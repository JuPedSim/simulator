#include "world_builder_binding.hpp"

#include <geometry/world_builder.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

void bind_world_builder(pybind11::module_ & m)
{
    pybind11::class_<WorldBuilder>(m, "WorldBuilder")
        .def(pybind11::init<>())
        .def("addLineSegment", &WorldBuilder::addLineSegment, "level"_a, "segment"_a)
        .def("addSpecialArea", &WorldBuilder::addSpecialArea, "level"_a, "area"_a);
}
