#include "coordinate_binding.hpp"

#include <geometry/coordinate.hpp>
#include <pybind11/operators.h>

void bind_coordinate(pybind11::module_ & m)
{
    pybind11::class_<jps::Coordinate>(m, "Coordinate")
        .def(pybind11::init<jps::LengthUnit, jps::LengthUnit>())
        .def_readwrite("x", &jps::Coordinate::x)
        .def_readwrite("y", &jps::Coordinate::y)
        // NOLINTNEXTLINE(misc-redundant-expression)
        .def(pybind11::detail::self == pybind11::detail::self)
        // NOLINTNEXTLINE(misc-redundant-expression)
        .def(pybind11::detail::self != pybind11::detail::self)
        .def(
            "__str__",
            [](const jps::Coordinate & coordinate) {
                return fmt::format(FMT_STRING("{}"), coordinate);
            })
        .def("__repr__", [](const jps::Coordinate & coordinate) {
            return fmt::format(FMT_STRING("{}"), coordinate);
        });
}
