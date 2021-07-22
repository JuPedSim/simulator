#include "world_binding.hpp"

#include <geometry/level_storage.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace pybind11::literals;

void bind_level_storage(pybind11::module_ & m)
{
    pybind11::class_<jps::LevelStorage>(m, "LevelStorage")
        .def("add_line_segment", &jps::LevelStorage::addLineSegment, "segment"_a)
        .def("add_special_area", &jps::LevelStorage::addSpecialArea, "area"_a)
        .def("add_agent", &jps::LevelStorage::addAgent, "agent"_a);
}
