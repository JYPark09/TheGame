#include <TheGame/Game/GameState.hpp>

namespace TheGame
{
GameResult GameState::GetResult() const
{
    if (!Finished)
        return GameResult::NOT_FINISHED;

    // TODO: implement this
    return GameResult::LOSE;
}
}  // namespace TheGame
