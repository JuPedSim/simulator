#include "line_segment_binding.hpp"

#include <geometry/line_segment.hpp>
#include <pybind11/operators.h>

void bind_line_segment(pybind11::module_ & m)
{
    pybind11::class_<jps::LineSegment>(m, "LineSegment")
        .def(pybind11::init<jps::Coordinate, jps::Coordinate>())
        .def(pybind11::init<jps::LineSegment const &>())
        .def(pybind11::detail::self == pybind11::detail::self) // NOLINTLINE
        .def(pybind11::detail::self != pybind11::detail::self) // NOLINTLINE
        .def_property_readonly("start", &jps::LineSegment::getStart)
        .def_property_readonly("end", &jps::LineSegment::getEnd)
        .def("rotate", &jps::LineSegment::rotate)
        .def(
            "__str__",
            [](const jps::LineSegment & coordinate) {
                return fmt::format(FMT_STRING("{}"), coordinate);
            })
        .def("__repr__", [](const jps::LineSegment & coordinate) {
            return fmt::format(FMT_STRING("{}"), coordinate);
        });
}
