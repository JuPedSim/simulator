#include <log.hpp>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <simulation.hpp>

namespace py = pybind11;

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
PYBIND11_MODULE(jpscore, m)
{
    py::class_<jps::Simulation>(m, "Simulation")
        .def(py::init<>())
        .def("get", &jps::Simulation::getValue);

    auto m_logging = m.def_submodule("logging");

    py::enum_<jps::Logging::Level>(m_logging, "Level")
        .value("Debug", jps::Logging::Level::Debug)
        .value("Info", jps::Logging::Level::Info)
        .value("Warning", jps::Logging::Level::Warning)
        .value("Error", jps::Logging::Level::Error);

    m_logging.def(
        "set_callback",
        [](jps::Logging::Level level, jps::Logging::LogCallback callback) {
            jps::Logging::setCallback(
                level, [callback = std::move(callback)](std::string_view msg) {
                    py::gil_scoped_acquire lock;
                    callback(msg);
                });
        },
        py::kw_only(),
        py::arg("level"),
        py::arg("func"));

    /// Regsitered python functions are wrapped by pybind11. These wrappers have to be
    /// destructed before the interpreter is shutown. Since python does not destroy modules
    /// on shutdown registering an atexit handler is probably the most robust way to ensure
    /// destruction.
    py::module_::import("atexit").attr("register")(py::cpp_function([]() {
        jps::Logging::setCallback(jps::Logging::Level::Debug, jps::Logging::LogCallback{});
        jps::Logging::setCallback(jps::Logging::Level::Info, jps::Logging::LogCallback{});
        jps::Logging::setCallback(jps::Logging::Level::Warning, jps::Logging::LogCallback{});
        jps::Logging::setCallback(jps::Logging::Level::Error, jps::Logging::LogCallback{});
    }));
}
