#include <pyTheGame/Cards/Card.hpp>

#include <TheGame/Cards/Card.hpp>

namespace py = pybind11;
using namespace TheGame;

void buildCard(py::module& m)
{
    py::class_<Card>(m, "Card")
        .def(py::init<int>())
        .def_readonly_static("MIN", &Card::Min)
        .def_readonly_static("MAX", &Card::Max)
        .def("is_valid", &Card::IsValid)
        .def("__int__", &Card::operator int);
}
