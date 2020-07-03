#ifndef PYTHEGAME_GAME_STATE_HPP
#define PYTHEGAME_GAME_STATE_HPP

#include <pybind11/pybind11.h>

void buildGameResult(pybind11::module& m);
void buildGameState(pybind11::module& m);

#endif  // PYTHEGAME_GAME_STATE_HPP
