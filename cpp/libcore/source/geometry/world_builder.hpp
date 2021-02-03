#ifndef SIMULATOR_WORLD_BUILDER_HPP
#define SIMULATOR_WORLD_BUILDER_HPP

#include "coordinate.hpp"
#include "line_segment.hpp"
#include "special_area.hpp"

#include <map>
#include <vector>

class WorldBuilder
{
private:
    std::map<int, std::vector<LineSegment>> m_level_to_boundary_lines;
    std::map<int, std::vector<SpecialArea>> m_level_to_special_areas;

public:
    WorldBuilder() = default;

    // TODO: somehow check for maximum dimensions and shift if necessary (to not exceed the int
    // range)

    void addBoundaryLine(LineSegment p_segment);
    void addSpecialArea(SpecialArea p_area);
};

#endif // SIMULATOR_WORLD_BUILDER_HPP
