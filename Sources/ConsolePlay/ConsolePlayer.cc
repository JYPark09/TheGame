#include <ConsolePlay/ConsolePlayer.hpp>

#include <TheGame/Game/Game.hpp>
#include <TheGame/Tasks/StackTask.hpp>

#include <algorithm>
#include <iostream>
#include <vector>

using namespace TheGame;

using std::cin;
using std::cout;
using std::endl;

ConsolePlayer::ConsolePlayer(Game& game, std::size_t pos)
    : Player(game), pos_(pos)
{
    // Do nothing
}

void ConsolePlayer::Invoke()
{
    cout << "[" << pos_ << " player turn]" << endl;

    printState();
    printCards();

    Task::Arr tasks;

    int card, pos;
    while (true)
    {
        cout << "Choose card to draw(input 0 to done): ";
        cin >> card;

        if (card == 0)
        {
            if (tasks.size() < game_.GetState().MinCardsToDraw)
            {
                cout << "ERROR: you must draw "
                     << game_.GetState().MinCardsToDraw << " card(s).\n";
                continue;
            }

            break;
        }

        auto it = std::find_if(begin(Cards), end(Cards),
                               [card](const Card& c) { return c == card; });
        if (it == end(Cards))
        {
            cout << "ERROR: invalid card.\n";
            continue;
        }

        cout << "Choose position to stack: ";
        cin >> pos;

        if (!(pos >= 0 && pos < GameState::STACK_COUNT) ||
            !game_.GetState().CardStacks[pos]->Stackable(*it))
        {
            cout << "ERROR: invalid position.\n";
            continue;
        }

        tasks.emplace_back(std::make_unique<StackTask>(*this, *it, pos));
    }

    game_.ProcessTurn(tasks);
}

void ConsolePlayer::printCards() const
{
    cout << "[Your hand]\n";

    for (const auto& c : Cards)
    {
        cout << static_cast<int>(c) << ' ';
    }
    cout << endl;
}

void ConsolePlayer::printState() const
{
    cout << "[Game State]\n";

    int pos = 0;
    for (const auto& s : game_.GetState().CardStacks)
    {
        cout << (pos++)
             << (s->GetType() == CardStack::Type::UP ? " [U  P] " : " [DOWN] ")
             << (static_cast<int>(s->TopCard())) << '\n';
    }
    cout << endl;
}
