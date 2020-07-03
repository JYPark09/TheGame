#include <iostream>

#include <TheGame/Game/Game.hpp>

#include <ConsolePlay/ConsolePlayer.hpp>

using std::cin;
using std::cout;
using std::endl;

int main()
{
    cout << "[TheGame console player]\n"
         << "Please enter the number of player: ";

    TheGame::Game game;

    int numOfPlayer;
    cin >> numOfPlayer;
    cin.ignore();

    while (numOfPlayer <= 0)
    {
        cout << "ERROR: invalid player number\n"
             << "Please enter the number of player: ";

        cin >> numOfPlayer;
        cin.ignore();
    }

    for (int i = 0; i < numOfPlayer; ++i)
        game.AddPlayer(std::make_unique<ConsolePlayer>(game, i + 1));

    cout << "\n\nNow start a game" << endl;
    game.Begin();

    while (game.GetState().Result == TheGame::GameResult::NOT_FINISHED)
    {
        auto& curPlayer = game.GetCurrentPlayer();

        curPlayer.Invoke();
    }

    if (game.GetState().Result == TheGame::GameResult::WIN)
    {
        cout << "Congraturation! You win" << endl;
    }
    else
    {
        cout << "You lose :(" << endl;
    }

    return EXIT_SUCCESS;
}
