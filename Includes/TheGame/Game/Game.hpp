#ifndef THEGAME_GAME_HPP
#define THEGAME_GAME_HPP

#include <TheGame/Game/GameState.hpp>
#include <TheGame/Game/Player.hpp>
#include <TheGame/Tasks/Task.hpp>

#include <memory>
#include <vector>

namespace TheGame
{
class Game final
{
 public:
    Game();
    Game(const Game&) = delete;
    Game(Game&&) = delete;

    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    void AddPlayer(Player* player);
    [[nodiscard]] std::size_t GetPlayerNumber() const;
    [[nodiscard]] std::size_t GetTurn() const;
    [[nodiscard]] Player& GetCurrentPlayer();
    [[nodiscard]] const Player& GetCurrentPlayer() const;
    [[nodiscard]] const GameState& GetState() const;

    void Begin();

    void InvokeCurrentPlayer();
    void ProcessTurn(Task::Arr& tasks);

 private:
    void updateResult();

 private:
    std::size_t turn_;
    std::vector<Player*> players_;

    GameState state_;
};
}  // namespace TheGame

#endif  // THEGAME_GAME_HPP
