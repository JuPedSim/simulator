#include "line_segment_binding.hpp"

#include <geometry/line_segment.hpp>
#include <pybind11/operators.h>

void bind_line_segment(pybind11::module_ & m)
{
    pybind11::class_<jps::LineSegment>(m, "LineSegment")
        .def(pybind11::init<jps::Coordinate, jps::Coordinate>())
        .def(pybind11::detail::self == pybind11::detail::self) // NOLINTLINE(misc-redundant-expression)
        .def(pybind11::detail::self != pybind11::detail::self) // NOLINTLINE(misc-redundant-expression)
        .def_property_readonly("start", &jps::LineSegment::getStart, pybind11::return_value_policy::copy)
        .def_property_readonly("end", &jps::LineSegment::getEnd, pybind11::return_value_policy::copy)
        .def("rotate", &jps::LineSegment::rotate)
        .def(
            "__str__",
            [](const jps::LineSegment & line_segment) {
                return fmt::format(FMT_STRING("{}"), line_segment);
            })
        .def("__repr__", [](const jps::LineSegment & line_segment) {
            return fmt::format(FMT_STRING("{}"), line_segment);
        });
}
