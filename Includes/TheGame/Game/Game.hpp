#ifndef THEGAME_GAME_HPP
#define THEGAME_GAME_HPP

#include <TheGame/Game/GameState.hpp>
#include <TheGame/Game/Player.hpp>

#include <memory>
#include <vector>

namespace TheGame
{
class Game final
{
 public:
    Game(const Game&) = delete;
    Game(Game&&) = delete;

    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    void AddPlayer(std::unique_ptr<Player>&& player);
    [[nodiscard]] std::size_t GetPlayerNumber() const;

    void Begin();

    bool ProcessTurn();

    [[nodiscard]] const GameState& GetState() const;

 private:
    std::vector<std::unique_ptr<Player>> players_;
    
   GameState state_;
};
}  // namespace TheGame

#endif  // THEGAME_GAME_HPP
