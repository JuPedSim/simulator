#include "world_builder_binding.hpp"

#include <geometry/world_builder.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace pybind11::literals;

void bind_world_builder(pybind11::module_ & m)
{
    pybind11::class_<jps::WorldBuilder>(m, "WorldBuilder")
        .def(pybind11::init<>())
        .def("addLineSegment", &jps::WorldBuilder::addLineSegment, "level"_a, "segment"_a)
        .def("addSpecialArea", &jps::WorldBuilder::addSpecialArea, "level"_a, "area"_a);
}
