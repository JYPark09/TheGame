#include <pyTheGame/Game/Player.hpp>

#include <TheGame/Game/Game.hpp>
#include <TheGame/Game/Player.hpp>

#include <pybind11/stl.h>

namespace py = pybind11;
using namespace TheGame;

void buildPlayer(py::module& m)
{
    py::class_<Player>(m, "Player")
        .def_readwrite("cards", &Player::Cards)
		.def("set_game", &Player::SetGame)
        .def("invoke", &Player::Invoke);
}
