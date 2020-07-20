import pyTheGame
import numpy as np

def print_game_state(state: pyTheGame.GameState):
    print('card stacks: ', end='')

    for stack in state.card_stacks:
        print(int(stack.top_card()), end=' ')
    print()

def print_hand(player: pyTheGame.Player):
    print('your hands: ', end='')

    for card in player.cards:
        print(int(card), end=' ')
    print()

# we need to present numbers from 1 to 100
# so, we need ceil(log_2(100))=7 bits for one card
BITS_FOR_NUM = 7
def bin_array(card: pyTheGame.Card):
    return np.array(list(np.binary_repr(int(card)).zfill(BITS_FOR_NUM))).astype(np.int8)


def card_stacks_to_tensor(state: pyTheGame.GameState):
    stack = []

    for i in range(state.STACK_COUNT):
        stack.append(bin_array(state.card_stacks[i].top_card()))

    return np.concatenate(stack)

def hands_to_tensor(player: pyTheGame.Game):
    max_of_hands = player.game.get_state().cards_to_have
    num_of_hands = len(player.cards)

    num_vec = np.zeros(max_of_hands).astype(np.int8)
    num_vec[num_of_hands-1] = 1

    hand_vec = np.zeros(max_of_hands * BITS_FOR_NUM).astype(np.int8)

    for i in range(num_of_hands):
        start_idx, end_idx = i*BITS_FOR_NUM, (i+1)*BITS_FOR_NUM
        hand_vec[start_idx:end_idx] = bin_array(player.cards[i])

    return np.concatenate((num_vec, hand_vec))

def state_to_tensor(player: pyTheGame.Player):
    card_stacks_tensor = card_stacks_to_tensor(player.game.get_state())
    hands_tensor = hands_to_tensor(player)

    return np.concatenate((card_stacks_tensor, hands_tensor))

def get_action_list(player: pyTheGame.Player):
    state = player.game.get_state()

    actions = []

    for i, card in enumerate(player.cards):
        for j in range(state.STACK_COUNT):
            actions.append((i, j))

    return actions

def action_mask(player: pyTheGame.Player):
    state = player.game.get_state()
    actions = get_action_list(player)

    mask = np.zeros(state.cards_to_have * state.STACK_COUNT)

    for action in actions:
        i, j = action

        if state.card_stacks[j].stackable(player.cards[i]):
            mask[i * state.STACK_COUNT + j] = 1

    return mask

if __name__ == '__main__':
    game = pyTheGame.Game()

    player = pyTheGame.FakePlayer()
    game.add_player(player)

    game.begin()

    print_game_state(game.get_state())
    print_hand(player)

    print(card_stacks_to_tensor(game.get_state()))
    print(hands_to_tensor(player))
    print(state_to_tensor(player))
    print(action_mask(player))

    game.process_turn(game, pyTheGame.StackTask(player.cards[0], 0))
    game.process_turn(game, pyTheGame.StackTask(player.cards[0], 1))
    game.end_turn()

    print()
    print_game_state(game.get_state())
    print_hand(player)

    print(card_stacks_to_tensor(game.get_state()))
    print(hands_to_tensor(player))
    print(state_to_tensor(player))
    print(action_mask(player))

