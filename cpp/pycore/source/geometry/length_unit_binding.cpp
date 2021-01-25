#include "geometry/length_unit.hpp"
#include "world_builder_binding.hpp"


void bind_length_unit(pybind11::module_ & m)
{
    pybind11::class_<jps::LengthUnit>(m, "LengthUnit")
        .def(pybind11::init<>(&jps::makeLengthUnit<jps::Units::m>))
        .def("get", &jps::LengthUnit::get<jps::Units::m>);
}
