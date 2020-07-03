#ifndef CONSOLE_PLAY_CONSOLE_PLAYER_HPP
#define CONSOLE_PLAY_CONSOLE_PLAYER_HPP

#include <TheGame/Game/Player.hpp>

class ConsolePlayer final : public TheGame::Player
{
 public:
    ConsolePlayer(TheGame::Game& game, std::size_t pos);

    void Invoke() override;

 private:
    void printCards() const;
    void printState() const;

 private:
    std::size_t pos_;
};

#endif  // CONSOLE_PLAY_CONSOLE_PLAYER_HPP
