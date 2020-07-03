#include <pyTheGame/Cards/CardStack.hpp>

#include <TheGame/Cards/CardStack.hpp>

namespace py = pybind11;
using namespace TheGame;

void buildCardStack(py::module& m)
{
    py::class_<CardStack> cs(m, "CardStack");
    cs.def(py::init<CardStack::Type>())
        .def("stackable", &CardStack::Stackable)
        .def("add_card", &CardStack::AddCard)
        .def("top_card", &CardStack::TopCard)
        .def("get_type", &CardStack::GetType);

    py::enum_<CardStack::Type>(cs, "Type")
        .value("UP", CardStack::Type::UP)
        .value("DOWN", CardStack::Type::DOWN)
        .export_values();
}
