#include "line_segment_binding.hpp"

#include <geometry/area.hpp>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

void bind_area(pybind11::module_ & m)
{
    pybind11::class_<jps::Area>(m, "Area")
        .def(pybind11::init<std::vector<jps::Coordinate>>())
        .def(pybind11::init<std::vector<jps::LineSegment>>())
        // NOLINTNEXTLINE(misc-redundant-expression)
        .def(pybind11::detail::self == pybind11::detail::self)
        // NOLINTNEXTLINE(misc-redundant-expression)
        .def(pybind11::detail::self != pybind11::detail::self)
        .def_property_readonly(
            "polygon", &jps::Area::getPolygon, pybind11::return_value_policy::copy)
        .def("__str__", [](const jps::Area & area) { return fmt::format(FMT_STRING("{}"), area); })
        .def(
            "__repr__", [](const jps::Area & area) { return fmt::format(FMT_STRING("{}"), area); });
}
