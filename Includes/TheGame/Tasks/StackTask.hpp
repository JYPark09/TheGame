#ifndef THEGAME_STACK_TASK_HPP
#define THEGAME_STACK_TASK_HPP

#include <TheGame/Cards/Card.hpp>
#include <TheGame/Tasks/Task.hpp>

namespace TheGame
{
class StackTask final : public Task
{
 public:
    StackTask(Card card, std::size_t position);

    void Process(GameState* state) override;

 private:
    Card card_;
    std::size_t position_;
};
}  // namespace TheGame

#endif  // THEGAME_STACK_TASK_HPP
