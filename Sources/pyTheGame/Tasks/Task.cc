#include <pyTheGame/Tasks/Task.hpp>

#include <TheGame/Tasks/Task.hpp>

namespace py = pybind11;
using namespace TheGame;

class PyTask : public Task
{
 public:
    using Task::Task;

    void Process(GameState* state) override
    {
        PYBIND11_OVERLOAD_PURE(void, Task, process, state);
    }
};

void buildTask(py::module& m)
{
    py::class_<Task, PyTask>(m, "Task")
        .def(py::init<>())
        .def("process", &Task::Process);
}
