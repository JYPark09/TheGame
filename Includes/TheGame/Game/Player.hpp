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
}  // namespace TheGame

#endif  // THEGAME_PLAYER_HPP
