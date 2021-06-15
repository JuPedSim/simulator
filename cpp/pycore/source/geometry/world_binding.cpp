#include "world_binding.hpp"

#include <geometry/world.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace pybind11::literals;

void bind_world(pybind11::module_ & m)
{
    pybind11::class_<jps::World>(m, "World")
        .def(pybind11::init<>())
        .def("addLineSegment", &jps::World::addLineSegment, "level"_a, "segment"_a)
        .def("addSpecialArea", &jps::World::addSpecialArea, "level"_a, "area"_a);
}