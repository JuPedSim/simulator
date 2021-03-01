#include "spatial_vector_binding.hpp"

#include <geometry/spatial_vector.hpp>
#include <pybind11/operators.h>

void bind_spatial_vector(pybind11::module_ & m)
{
    pybind11::class_<jps::SpatialVector>(m, "SpatialVector")
        .def(pybind11::init<jps::LengthUnit, jps::LengthUnit>())
        .def_readwrite("x", &jps::SpatialVector::x)
        .def_readwrite("y", &jps::SpatialVector::y)
        .def(pybind11::detail::self == pybind11::detail::self) // NOLINTLINE(misc-redundant-expression)
        .def(pybind11::detail::self != pybind11::detail::self) // NOLINTLINE(misc-redundant-expression)
        .def(
            "__str__",
            [](const jps::SpatialVector & spatial_vector) {
                return fmt::format(FMT_STRING("{}"), spatial_vector);
            })
        .def("__repr__", [](const jps::SpatialVector & spatial_vector) {
            return fmt::format(FMT_STRING("{}"), spatial_vector);
        });
}
