#include "level_binding.hpp"

#include <geometry/level.hpp>
#include <pybind11/operators.h>

void bind_level(pybind11::module_ & m)
{
    pybind11::class_<jps::Level>(m, "Level")
        .def(pybind11::init<std::int32_t>())
        .def("id", &jps::Level::id, pybind11::return_value_policy::copy)
        // NOLINTNEXTLINE(misc-redundant-expression)
        .def(pybind11::detail::self == pybind11::detail::self)
        // NOLINTNEXTLINE(misc-redundant-expression)
        .def(pybind11::detail::self != pybind11::detail::self)
        .def(
            "__str__",
            [](const jps::Level & level) { return fmt::format(FMT_STRING("{}"), level); })
        .def("__repr__", [](const jps::Level & level) {
            return fmt::format(FMT_STRING("{}"), level);
        });

    ;
}
