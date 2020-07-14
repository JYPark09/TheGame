import pyTheGame
from utils import BITS_FOR_NUM, state_to_tensor, get_action_list, action_mask

import torch
from torch import nn, optim
import torch.nn.functional as F
from torch.distributions import Categorical

import numpy as np

device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')

N_HANDS = 8
N_STACKS = 4
N_OBS = BITS_FOR_NUM * (N_HANDS + N_STACKS) + N_HANDS

GAMMA = 0.99

class Network(nn.Module):
    def __init__(self, n_obs: int, n_hands: int, n_stacks: int):
        super(Network, self).__init__()

        self.fc1 = nn.Linear(n_obs, 256)
        self.fc2 = nn.Linear(256, 256)
        self.fc3 = nn.Linear(256, 256)
        self.fc4 = nn.Linear(256, n_hands*n_stacks + 1)

        self.relu = nn.ReLU(inplace=True)

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        x = self.relu(self.fc1(x))
        x = self.relu(self.fc2(x))
        x = self.relu(self.fc3(x))

        return self.fc4(x)

class REINFORCEAgent(pyTheGame.Player):
    def __init__(self):
        super(REINFORCEAgent, self).__init__()

        self.net = Network(N_OBS, N_HANDS, N_STACKS).to(device)
        self.opt = optim.SGD(self.net.parameters(), lr=1e-3, weight_decay=1e-4, momentum=.9, nesterov=True)

        self.log_pi_buf = []
        self.reward_buf = []

    def invoke(self):
        cards_to_draw = self.game.get_state().min_cards_to_draw

        drawed = 0
        while True:
            state = state_to_tensor(self)
            state_t = torch.FloatTensor(state).to(device)

            mask = np.concatenate((action_mask(self), [1 if drawed >= cards_to_draw else 0]))
            if sum(mask) == 0:
                break
            
            mask = torch.BoolTensor(mask).to(device)

            policy_logits = self.net(state_t)
            policy_logits = torch.where(mask, policy_logits, torch.tensor(-1e+10).to(device))

            m = Categorical(logits=policy_logits)

            action = m.sample()
            self.log_pi_buf.append(m.log_prob(action))
            self.reward_buf.append(1)

            action = action.item()
            actions = get_action_list(self)

            if action == len(mask) - 1:
                break

            card_idx, stack_idx = actions[action]
            self.game.process_turn(self.game, pyTheGame.StackTask(self.cards[card_idx], stack_idx))

            drawed += 1

        self.game.end_turn()

    def train(self):
        if len(self.reward_buf) == 0:
            return

        G = 0
        returns = []
        for reward in self.reward_buf[::-1]:
            G = reward + GAMMA * G
            returns.insert(0, G)

        returns = torch.FloatTensor(returns)
        returns = (returns - returns.mean()) / (returns.std() + 1e-10)

        losses = []
        for log_pi, ret in zip(self.log_pi_buf, returns):
            losses.append(-log_pi * ret)

        self.opt.zero_grad()

        loss = sum(losses)
        loss.backward()

        self.opt.step()

        self.log_pi_buf = []
        self.reward_buf = []
