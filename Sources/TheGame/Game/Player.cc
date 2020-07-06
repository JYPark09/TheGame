#include <TheGame/Game/Player.hpp>

namespace TheGame
{
void Player::SetGame(Game* game)
{
    game_ = game;
}

void FakePlayer::Invoke()
{
	// Do nothing
}
}  // namespace TheGame
