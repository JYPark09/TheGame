#ifndef THEGAME_TASK_HPP
#define THEGAME_TASK_HPP

#include <TheGame/Game/GameState.hpp>

#include <vector>

namespace TheGame
{
class Task
{
public:
    using Arr = std::vector<Task>;

public:
    virtual void Process(GameState& state) = 0;
};
}

#endif  // THEGAME_TASK_HPP
