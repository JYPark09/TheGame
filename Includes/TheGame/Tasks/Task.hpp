#ifndef THEGAME_TASK_HPP
#define THEGAME_TASK_HPP

#include <TheGame/Game/GameState.hpp>
#include <TheGame/Game/Player.hpp>

#include <memory>

namespace TheGame
{
class Task
{
 public:
    Player* player_{ nullptr };
    void SetPlayer(Player* player);

    virtual void Process(GameState* state) = 0;
};
}  // namespace TheGame

#endif  // THEGAME_TASK_HPP
