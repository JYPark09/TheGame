#include <pyTheGame/Game/GameState.hpp>

#include <TheGame/Game/GameState.hpp>

#include <pybind11/stl.h>

namespace py = pybind11;
using namespace TheGame;

void buildGameResult(py::module& m)
{
    py::enum_<GameResult>(m, "GameResult")
        .value("NOT_FINISHED", GameResult::NOT_FINISHED)
        .value("WIN", GameResult::WIN)
        .value("LOSE", GameResult::LOSE)
        .export_values();
}

void buildGameState(py::module& m)
{
    py::class_<GameState>(m, "GameState")
        .def_readonly_static("STACK_COUNT", &GameState::STACK_COUNT)
        .def_readwrite("cards_to_have", &GameState::CardsToHave)
        .def_readwrite("min_cards_to_have", &GameState::MinCardsToDraw)
        .def_readwrite("result", &GameState::Result)
        .def_readwrite("cards", &GameState::Cards)
        .def_readwrite("card_stacks", &GameState::CardStacks);
}
