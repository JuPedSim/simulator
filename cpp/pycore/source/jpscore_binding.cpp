#include "geometry/level_binding.hpp"
#include "geometry/world_builder_binding.hpp"
#include "logging_binding.hpp"
#include "simulation_binding.hpp"

#include <pybind11/pybind11.h>

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
PYBIND11_MODULE(jpscore, m)
{
    /// MODULE jpscore
    bind_simulation(m);

    /// SUB MODULE logging
    auto m_logging = m.def_submodule("logging");
    bind_logging(m_logging);

    /// SUB MODULE geometry
    auto m_geometry = m.def_submodule("geometry");
    bind_level(m_geometry);
    bind_world_builder(m_geometry);
}
