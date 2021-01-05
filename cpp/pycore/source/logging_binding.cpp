#include "logging_binding.hpp"

#include <log.hpp>
#include <pybind11/functional.h>

void bind_logging(pybind11::module_ & m)
{
    pybind11::enum_<jps::Logging::Level>(m, "Level")
        .value("Debug", jps::Logging::Level::Debug)
        .value("Info", jps::Logging::Level::Info)
        .value("Warning", jps::Logging::Level::Warning)
        .value("Error", jps::Logging::Level::Error);

    m.def(
        "set_callback",
        [](jps::Logging::Level level, jps::Logging::LogCallback callback) {
            jps::Logging::setCallback(
                level, [callback = std::move(callback)](std::string_view msg) {
                    pybind11::gil_scoped_acquire lock;
                    callback(msg);
                });
        },
        pybind11::kw_only(),
        pybind11::arg("level"),
        pybind11::arg("func"));

    /// Regsitered python functions are wrapped by pybind11. These wrappers have to be
    /// destructed before the interpreter is shutown. Since python does not destroy modules
    /// on shutdown registering an atexit handler is probably the most robust way to ensure
    /// destruction.
    pybind11::module_::import("atexit").attr("register")(pybind11::cpp_function([]() {
        jps::Logging::setCallback(jps::Logging::Level::Debug, jps::Logging::LogCallback{});
        jps::Logging::setCallback(jps::Logging::Level::Info, jps::Logging::LogCallback{});
        jps::Logging::setCallback(jps::Logging::Level::Warning, jps::Logging::LogCallback{});
        jps::Logging::setCallback(jps::Logging::Level::Error, jps::Logging::LogCallback{});
    }));
}
