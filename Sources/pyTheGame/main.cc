#include <pybind11/pybind11.h>

#include <pyTheGame/Cards/Card.hpp>
#include <pyTheGame/Cards/CardStack.hpp>

#include <pyTheGame/Game/Game.hpp>
#include <pyTheGame/Game/GameState.hpp>
#include <pyTheGame/Game/Player.hpp>

#include <pyTheGame/Tasks/StackTask.hpp>
#include <pyTheGame/Tasks/Task.hpp>

PYBIND11_MODULE(pyTheGame, m)
{
    m.doc() = R"pbdoc(TheGame simulator)pbdoc";

    buildCard(m);
    buildCardStack(m);
    
	buildGame(m);
    buildGameResult(m);
    buildGameState(m);
	buildPlayer(m);

    buildTask(m);
    buildStackTask(m);
}
