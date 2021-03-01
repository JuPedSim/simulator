#include "length_unit_binding.hpp"

#include <geometry/length_unit.hpp>
#include <pybind11/operators.h>

void bind_length_unit(pybind11::module_ & m)
{
    pybind11::enum_<jps::Units>(m, "Units")
        .value("um", jps::Units::um)
        .value("mm", jps::Units::mm)
        .value("cm", jps::Units::cm)
        .value("dm", jps::Units::dm)
        .value("m", jps::Units::m)
        .value("km", jps::Units::km)
        .export_values();

    pybind11::class_<jps::LengthUnit>(m, "LengthUnit")
        .def(pybind11::init<>(&jps::makeLengthUnit<jps::Units::m>))
        .def(pybind11::detail::self == pybind11::detail::self) // NOLINTLINE(misc-redundant-expression)
        .def(pybind11::detail::self != pybind11::detail::self) // NOLINTLINE(misc-redundant-expression)
        .def(
            "__str__",
            [](const jps::LengthUnit & length_unit) {
                return fmt::format(FMT_STRING("{}"), length_unit);
            })
        .def("__repr__", [](const jps::LengthUnit & length_unit) {
            return fmt::format(FMT_STRING("{}"), length_unit);
        });
}
