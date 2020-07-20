from agent import REINFORCEAgent

import pyTheGame

NUM_EPISODES = 5000

agent = REINFORCEAgent()

for ep in range(1, NUM_EPISODES + 1):
    game = pyTheGame.Game()
    game.add_player(agent)

    game.begin()

    while game.get_state().result == pyTheGame.GameResult.NOT_FINISHED:
        cur_player = game.get_current_player()

        cur_player.invoke()

    ep_reward = sum(agent.reward_buf)

    print('[episode {}] reward: {}'.format(ep, ep_reward))
    agent.train()
