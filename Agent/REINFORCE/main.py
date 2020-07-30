from agent import REINFORCEAgent

import pyTheGame

from torch.utils.tensorboard import SummaryWriter

NUM_EPISODES = 30000

writer = SummaryWriter()

agent = REINFORCEAgent()

for ep in range(1, NUM_EPISODES + 1):
    game = pyTheGame.Game()
    game.add_player(agent)

    game.begin()

    while game.get_state().result == pyTheGame.GameResult.NOT_FINISHED:
        cur_player = game.get_current_player()

        cur_player.invoke()

    ep_reward, ep_loss = agent.train()
    print('[episode {}] reward: {}'.format(ep, ep_reward))

    writer.add_scalar('ep_loss', ep_loss, ep)
    writer.add_scalar('ep_reward', int(ep_reward*98), ep)

    for name, param in agent.net.named_parameters():
        writer.add_histogram(name, param.clone().cpu().data.numpy(), ep)

