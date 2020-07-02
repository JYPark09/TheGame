#ifndef THEGAME_PLAYER_HPP
#define THEGAME_PLAYER_HPP

#include <TheGame/Cards/Card.hpp>

namespace TheGame
{
class Game;

class Player
{
 public:
    Player(Game& game);
    virtual void Invoke() = 0;

 protected:
    Game& game_;

    Card::Arr cards_;
};
}  // namespace TheGame

#endif  // THEGAME_PLAYER_HPP