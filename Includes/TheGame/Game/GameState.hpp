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
    bool Finished;

    Card::Arr Cards;
    std::array<CardStack::Ptr, STACK_COUNT> CardStacks;

    GameResult GetResult() const;
};
}  // namespace TheGame

#endif  // THEGAME_GAME_STATE_HPP
