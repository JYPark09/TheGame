#include <TheGame/Tasks/StackTask.hpp>

namespace TheGame
{
StackTask::StackTask(Player& player, const Card& card, std::size_t position)
    : Task(player), card_(card), position_(position)
{
    // Do nothing
}

void StackTask::Process()
{
}
}  // namespace TheGame
