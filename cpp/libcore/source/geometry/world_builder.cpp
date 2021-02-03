#include "world_builder.hpp"

#include <utility>

auto WorldBuilder::addBoundaryLine(LineSegment p_segment) -> void
{
    if(m_level_to_boundary_lines.find(p_segment.getLevel()) != m_level_to_boundary_lines.end()) {
        // push back if not empty
        m_level_to_boundary_lines[p_segment.getLevel()].push_back(p_segment);
    } else {
        // create new vector
        m_level_to_boundary_lines[p_segment.getLevel()] = std::vector<Line>{p_segment};
    }
}

auto WorldBuilder::addSpecialArea(SpecialArea p_area) -> void
{
    // TODO: check if area id at given level already exists

    if(m_level_to_special_areas.find(p_area.getLevel()) != (m_level_to_special_areas.end())) {
        // push back if not empty
        m_level_to_special_areas[p_area.getLevel()].push_back(p_area);
    } else {
        // create new vector
        m_level_to_special_areas[p_area.getLevel()] = std::vector<SpecialArea>{p_area};
    }
}
