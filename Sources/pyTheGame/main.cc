#include <pybind11/pybind11.h>

#include <pyTheGame/Cards/Card.hpp>
#include <pyTheGame/Cards/CardStack.hpp>

#include <pyTheGame/Game/GameState.hpp>

PYBIND11_MODULE(pyTheGame, m)
{
    m.doc() = R"pbdoc(TheGame simulator)pbdoc";

    buildCard(m);
    buildCardStack(m);

    buildGameResult(m);
    buildGameState(m);
}
