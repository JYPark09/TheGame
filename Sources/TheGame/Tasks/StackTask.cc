#include <TheGame/Tasks/StackTask.hpp>

#include <algorithm>

namespace TheGame
{
StackTask::StackTask(Card card, std::size_t position)
    : card_(std::move(card)), position_(position)
{
    // Do nothing
}

void StackTask::Process(GameState* state)
{
    const auto it = std::find(begin(player_->Cards), end(player_->Cards), card_);
    player_->Cards.erase(it);

    state->CardStacks[position_]->AddCard(card_);
}
}  // namespace TheGame
