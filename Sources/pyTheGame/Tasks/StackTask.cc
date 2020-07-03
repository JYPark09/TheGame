#include <pyTheGame/Tasks/StackTask.hpp>

#include <TheGame/Tasks/StackTask.hpp>

namespace py = pybind11;
using namespace TheGame;

void buildStackTask(py::module& m)
{
    py::class_<StackTask, Task>(m, "StackTask")
        .def(py::init<Card, std::size_t>());
}
