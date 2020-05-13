#ifndef THEGAME_GAME_HPP
#define THEGAME_GAME_HPP

#include <TheGame/Cards/CardStack.hpp>
#include <TheGame/Game/Player.hpp>

#include <memory>
#include <vector>

namespace TheGame
{
class Game final
{
 public:
    static constexpr std::size_t STACK_COUNT = 4;

    enum class Result
    {
        NOT_FINISHED,
        WIN,
        LOSE
    };

 public:
    Game(const Game&) = delete;
    Game(Game&&) = delete;

    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    void AddPlayer(std::unique_ptr<Player>&& player);
    [[nodiscard]] std::size_t GetPlayerNumber() const;

    void Begin();

    [[nodiscard]] bool IsEnd() const;
    [[nodiscard]] Result GetResult() const;

    [[nodiscard]] std::size_t GetMinCardsToDraw() const;

 private:
    std::vector<std::unique_ptr<Player>> players_;

    std::size_t cardsToHave_{ 0 };
    std::size_t minCardsToDraw_{ 0 };
    bool finished_{ true };

    std::vector<Card> cards_;
    std::unique_ptr<CardStack> stacks_[STACK_COUNT];
};
}  // namespace TheGame

#endif  // THEGAME_GAME_HPP
