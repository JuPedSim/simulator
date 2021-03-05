#include "special_area_binding.hpp"

#include <geometry/special_area.hpp>
#include <pybind11/operators.h>

void bind_special_area(pybind11::module_ & m)
{
    pybind11::class_<jps::SpecialArea>(m, "SpecialArea")
        .def(pybind11::init<std::uint32_t, jps::Area>())
        .def_property_readonly(
            "external_id", &jps::SpecialArea::getExternalID, pybind11::return_value_policy::copy)
        .def_property_readonly("id", &jps::SpecialArea::getID, pybind11::return_value_policy::copy)
        .def_property_readonly(
            "area", &jps::SpecialArea::getArea, pybind11::return_value_policy::copy)
        .def(
            "__str__",
            [](const jps::SpecialArea & special_area) {
                return fmt::format(FMT_STRING("{}"), special_area);
            })
        .def("__repr__", [](const jps::SpecialArea & special_area) {
            return fmt::format(FMT_STRING("{}"), special_area);
        });
}
