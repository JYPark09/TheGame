#ifndef THEGAME_PLAYER_HPP
#define THEGAME_PLAYER_HPP

namespace TheGame
{
class Game;

class Player
{
public:
    virtual void Invoke(Game& game) = 0;
};
}  // namespace TheGame

#endif  // THEGAME_PLAYER_HPP