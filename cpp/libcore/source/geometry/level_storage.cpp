#include "level_storage.hpp"

#include <algorithm>

namespace jps
{
auto LevelStorage::addLineSegment(LineSegment const & p_segment) -> void
{
    m_line_segments.push_back(p_segment);
}

auto LevelStorage::addSpecialArea(SpecialArea const & p_area) -> void
{
    m_special_areas.push_back(p_area);
}

auto LevelStorage::addAgent(Coordinate const & p_coordinate) -> void
{
    m_agents.emplace_back(Agent{p_coordinate});
}

auto LevelStorage::computeBoundingBox() -> BoundingBox
{
    // vector to store all coordinates
    std::vector<Coordinate> all_coordinates;

    // extract all coordinates from different components of level storage
    // extract from line segments
    for(const auto & line_segment : m_line_segments) {
        all_coordinates.push_back(line_segment.getStart());
        all_coordinates.push_back(line_segment.getEnd());
    }

    // extract from special areas
    for(const auto & special_area : m_special_areas) {
        auto polygon_coordinates = special_area.getArea().getPolygon();
        all_coordinates.insert(
            all_coordinates.end(), polygon_coordinates.begin(), polygon_coordinates.end());
    }
    // extract from agents
    for(const auto & agent : m_agents) {
        all_coordinates.push_back(agent.pos);
    }

    // get max/min x- and y-components
    auto [min_x, max_x] = std::minmax_element(
        all_coordinates.begin(),
        all_coordinates.end(),
        [](auto p_coord_first, auto p_coord_second) { return p_coord_first.x < p_coord_second.x; });
    auto [min_y, max_y] = std::minmax_element(
        all_coordinates.begin(),
        all_coordinates.end(),
        [](auto p_coord_first, auto p_coord_second) { return p_coord_first.y < p_coord_second.y; });

    return BoundingBox(Coordinate(min_x->x, min_y->y), Coordinate(max_x->x, max_y->y));
}

} // namespace jps
