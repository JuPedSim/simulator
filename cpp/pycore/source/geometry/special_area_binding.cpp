#include "special_area_binding.hpp"

#include <geometry/special_area.hpp>
#include <pybind11/operators.h>

void bind_special_area(pybind11::module_ & m)
{
    pybind11::class_<jps::SpecialArea>(m, "SpecialArea")
        .def(pybind11::init<std::uint32_t, jps::Area>())
        .def_property_readonly("external_id", &jps::SpecialArea::getExternalID)
        .def_property_readonly("id", &jps::SpecialArea::getID)
        .def_property_readonly("area", &jps::SpecialArea::getArea)
        .def(
            "__str__",
            [](const jps::LineSegment & coordinate) {
                return fmt::format(FMT_STRING("{}"), coordinate);
            })
        .def("__repr__", [](const jps::LineSegment & coordinate) {
            return fmt::format(FMT_STRING("{}"), coordinate);
        });
}
