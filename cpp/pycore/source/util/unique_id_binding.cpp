#include "unique_id_binding.hpp"

#include <agent/agent.hpp>
#include <pybind11/operators.h>
#include <util/unique_id.hpp>

void bind_unique_id(pybind11::module_ & m)
{
    pybind11::class_<jps::UniqueId<jps::Agent>>(m, "UniqueIDAgent")
        .def(pybind11::init<>())
        .def_property_readonly("id", &jps::UniqueId<jps::Agent>::getID)
        // NOLINTNEXTLINE(misc-redundant-expression)
        .def(pybind11::detail::self == pybind11::detail::self)
        // NOLINTNEXTLINE(misc-redundant-expression)
        .def(pybind11::detail::self != pybind11::detail::self)
        .def(
            "__str__",
            [](const jps::UniqueId<jps::Agent> & id) { return fmt::format(FMT_STRING("{}"), id); })
        .def("__repr__", [](const jps::UniqueId<jps::Agent> & id) {
            return fmt::format(FMT_STRING("{}"), id);
        });
}