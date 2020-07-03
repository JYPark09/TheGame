#ifndef THEGAME_PLAYER_HPP
#define THEGAME_PLAYER_HPP

#include <TheGame/Cards/Card.hpp>

namespace TheGame
{
class Game;

class Player
{
 public:
    Card::Arr Cards;

    void SetGame(Game* game);
    virtual void Invoke() = 0;

 protected:
    Game* game_{ nullptr };
};
}  // namespace TheGame

#endif  // THEGAME_PLAYER_HPP
