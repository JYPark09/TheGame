#ifndef THEGAME_PLAYER_HPP
#define THEGAME_PLAYER_HPP

#include <TheGame/Cards/Card.hpp>

namespace TheGame
{
class Game;

class Player
{
 public:
    Game* game_{ nullptr };
    Card::Arr Cards;

    void SetGame(Game* game);
    virtual void Invoke() = 0;
};

class FakePlayer : public Player
{
 public:
	void Invoke() override;
};
}  // namespace TheGame

#endif  // THEGAME_PLAYER_HPP
