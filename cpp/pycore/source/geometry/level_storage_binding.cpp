#include "world_binding.hpp"

#include <geometry/level_storage.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace pybind11::literals;

void bind_level_storage(pybind11::module_ & m)
{
    pybind11::class_<jps::LevelStorage>(m, "LevelStorage")
        .def("addLineSegment", &jps::LevelStorage::addLineSegment, "segment"_a)
        .def("addSpecialArea", &jps::LevelStorage::addSpecialArea, "area"_a);
}
