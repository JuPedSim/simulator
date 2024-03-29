#include "agent/agent_binding.hpp"
#include "geometry/area_binding.hpp"
#include "geometry/coordinate_binding.hpp"
#include "geometry/length_unit_binding.hpp"
#include "geometry/level_binding.hpp"
#include "geometry/level_storage_binding.hpp"
#include "geometry/line_segment_binding.hpp"
#include "geometry/spatial_vector_binding.hpp"
#include "geometry/special_area_binding.hpp"
#include "geometry/world_binding.hpp"
#include "logging_binding.hpp"
#include "simulation_binding.hpp"
#include "util/jpsexception_binding.hpp"
#include "util/simulation_clock_binding.hpp"
#include "util/unique_id_binding.hpp"

#include <pybind11/pybind11.h>

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
PYBIND11_MODULE(jpscore, m)
{
    /// MODULE jpscore
    bind_agent(m);
    bind_jpsexception(m);
    bind_simulation_clock(m);
    bind_simulation(m);
    bind_unique_id(m);

    /// SUB MODULE logging
    auto m_logging = m.def_submodule("logging");
    bind_logging(m_logging);

    /// SUB MODULE geometry
    auto m_geometry = m.def_submodule("geometry");
    bind_area(m_geometry);
    bind_coordinate(m_geometry);
    bind_length_unit(m_geometry);
    bind_level(m_geometry);
    bind_line_segment(m_geometry);
    bind_spatial_vector(m_geometry);
    bind_special_area(m_geometry);
    bind_world(m_geometry);
    bind_level_storage(m_geometry);
}
