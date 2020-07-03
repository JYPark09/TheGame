#include <pybind11/pybind11.h>

#include <pyTheGame/Cards/Card.hpp>
#include <pyTheGame/Cards/CardStack.hpp>

PYBIND11_MODULE(pyTheGame, m)
{
    m.doc() = R"pbdoc(TheGame simulator)pbdoc";

    buildCard(m);
    buildCardStack(m);
}