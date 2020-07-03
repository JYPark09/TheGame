#include <pyTheGame/Game/Game.hpp>

#include <TheGame/Game/Game.hpp>

namespace py = pybind11;
using namespace TheGame;

void buildGame(py::module& m)
{
	py::class_<Game>(m, "Game")
		.def(py::init<>())
		.def("add_player", &Game::AddPlayer)
		.def("get_player_number", &Game::GetPlayerNumber)
		.def("get_turn", &Game::GetTurn)
		.def("get_current_player", py::overload_cast<>(&Game::GetCurrentPlayer), py::return_value_policy::reference)
		.def("get_current_player_const", py::overload_cast<>(&Game::GetCurrentPlayer, py::const_), py::return_value_policy::reference)
		.def("get_state", &Game::GetState)
		.def("begin", &Game::Begin)
		.def("invoke_current_player", &Game::InvokeCurrentPlayer)
		.def_static("process_turn", [](Game* this_, Task* task) { this_->ProcessTurn(std::move(*task)); })
		.def("end_turn", &Game::EndTurn);
}

