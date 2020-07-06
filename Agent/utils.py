import pyTheGame
import numpy as np

def print_game_state(state):
    print('card stacks: ', end='')

    for stack in state.card_stacks:
        print(int(stack.top_card()), end=' ')
    print()

def print_hand(player):
    print('your hands: ', end='')

    for card in player.cards:
        print(int(card), end=' ')
    print()

# we need to present numbers from 1 to 100
# so, we need ceil(log_2(100))=7 bits for one card
BITS_FOR_NUM = 7
def bin_array(card):
    return np.array(list(np.binary_repr(int(card)).zfill(BITS_FOR_NUM))).astype(np.int8)


def card_stacks_to_tensor(state):
    stack_0 = bin_array(state.card_stacks[0].top_card())
    stack_1 = bin_array(state.card_stacks[1].top_card())
    stack_2 = bin_array(state.card_stacks[2].top_card())
    stack_3 = bin_array(state.card_stacks[3].top_card())

    return np.concatenate((stack_0, stack_1, stack_2, stack_3))

def hands_to_tensor(player):
    max_of_hands = player.game.get_state().cards_to_have
    num_of_hands = len(player.cards)

    num_vec = np.zeros(max_of_hands).astype(np.int8)
    num_vec[num_of_hands-1] = 1

    hand_vec = np.zeros(max_of_hands * BITS_FOR_NUM).astype(np.int8)

    for i in range(num_of_hands):
        start_idx, end_idx = i*BITS_FOR_NUM, (i+1)*BITS_FOR_NUM
        hand_vec[start_idx:end_idx] = bin_array(player.cards[i])

    return np.concatenate((num_vec, hand_vec))

def state_to_tensor(player):
    card_stacks_tensor = card_stacks_to_tensor(player.game.get_state())
    hands_tensor = hands_to_tensor(player)

    return np.concatenate((card_stacks_tensor, hands_tensor))

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

