#ifndef SIMULATOR_WORLD_BUILDER_HPP
#define SIMULATOR_WORLD_BUILDER_HPP

#include "line_segment.hpp"
#include "special_area.hpp"

#include <map>
#include <vector>

class WorldBuilder
{
private:
    std::map<int, std::vector<jps::LineSegment>> m_level_to_boundary_lines;
    std::map<int, std::vector<jps::SpecialArea>> m_level_to_special_areas;

public:
    WorldBuilder() = default;

    void addBoundaryLine(const jps::LineSegment &p_segment);
    void addSpecialArea(const jps::SpecialArea &p_area);
};

#endif // SIMULATOR_WORLD_BUILDER_HPP
