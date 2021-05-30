#include "length_unit_binding.hpp"

#include <geometry/length_unit.hpp>
#include <pybind11/operators.h>
#include <stdexcept>

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

    auto lu_binding = pybind11::class_<jps::LengthUnit>(m, "LengthUnit");
    // Constructor switching the unit to the corresponding template parameter
    lu_binding.def(pybind11::init([](jps::LengthUnit::QuantityType quantity, jps::Units unit) {
        switch(unit) {
            case jps::Units::um:
                return jps::makeLengthUnit<jps::Units::um>(quantity);
                break;
            case jps::Units::mm:
                return jps::makeLengthUnit<jps::Units::mm>(quantity);
                break;
            case jps::Units::cm:
                return jps::makeLengthUnit<jps::Units::cm>(quantity);
                break;
            case jps::Units::dm:
                return jps::makeLengthUnit<jps::Units::dm>(quantity);
                break;
            case jps::Units::m:
                return jps::makeLengthUnit<jps::Units::m>(quantity);
                break;
            case jps::Units::km:
                return jps::makeLengthUnit<jps::Units::km>(quantity);
                break;
            default:
                // TODO (kkz) remove the default and instead enable compiler warning that all cases
                // are handled.
                throw std::runtime_error(fmt::format(
                    FMT_STRING("Unit ({}) not yet implemented in python bindings."), unit));
        }
    }));
    // Read only parameters for getting the length unit quantity in desired unit
    lu_binding.def_property_readonly(
        "um", &jps::LengthUnit::get<jps::Units::um>, "Retreive the quantity in micrometer");
    lu_binding.def_property_readonly(
        "mm", &jps::LengthUnit::get<jps::Units::mm>, "Retreive the quantity in millimeter");
    lu_binding.def_property_readonly(
        "cm", &jps::LengthUnit::get<jps::Units::cm>, "Retreive the quantity in centimeter");
    lu_binding.def_property_readonly(
        "dm", &jps::LengthUnit::get<jps::Units::dm>, "Retreive the quantity in decimeter");
    lu_binding.def_property_readonly(
        "m", &jps::LengthUnit::get<jps::Units::m>, "Retreive the quantity in meter");
    lu_binding.def_property_readonly(
        "km", &jps::LengthUnit::get<jps::Units::km>, "Retreive the quantity in kilometer");
    // Comparison operators
    lu_binding.def(pybind11::detail::self == pybind11::detail::self); // NOLINTLINE
    lu_binding.def(pybind11::detail::self != pybind11::detail::self); // NOLINTLINE
    // magic function for string
    lu_binding.def("__str__", [](const jps::LengthUnit & length_unit) {
        return fmt::format(FMT_STRING("{}"), length_unit);
    });
    lu_binding.def("__repr__", [](const jps::LengthUnit & length_unit) {
        return fmt::format(FMT_STRING("{}"), length_unit);
    });
}
