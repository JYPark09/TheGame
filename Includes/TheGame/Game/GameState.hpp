#ifndef THEGAME_GAME_STATE_HPP
#define THEGAME_GAME_STATE_HPP

#include <TheGame/Cards/CardStack.hpp>

#include <array>

namespace TheGame
{
enum class GameResult
{
    NOT_FINISHED,
    WIN,
    LOSE
};

struct GameState final
{
    static constexpr std::size_t STACK_COUNT = 4;

    std::size_t CardsToHave;
    std::size_t MinCardsToDraw;
    GameResult Result;

    Card::Arr Cards;
    std::array<CardStack*, STACK_COUNT> CardStacks;
};
}  // namespace TheGame

#endif  // THEGAME_GAME_STATE_HPP
