#include <pyTheGame/Game/Player.hpp>

#include <TheGame/Game/Game.hpp>
#include <TheGame/Game/Player.hpp>

#include <pybind11/stl.h>

namespace py = pybind11;
using namespace TheGame;

class PyPlayer : public Player
{
 public:
    using Player::Player;

    void Invoke() override
    {
        PYBIND11_OVERLOAD_PURE(void, Player, invoke);
    }
};

void buildPlayer(py::module& m)
{
    py::class_<Player, PyPlayer>(m, "Player")
        .def(py::init<>())
        .def_readwrite("cards", &Player::Cards)
        .def_readwrite("game", &Player::game_)
        .def("set_game", &Player::SetGame)
        .def("invoke", &Player::Invoke);

	py::class_<FakePlayer, Player>(m, "FakePlayer")
		.def(py::init<>())
		.def("invoke", &FakePlayer::Invoke);
}

