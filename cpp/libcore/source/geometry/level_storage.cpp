#include "level_storage.hpp"

namespace jps
{
auto LevelStorage::addLineSegment(LineSegment const & p_segment) -> void
{
    m_line_segments.push_back(p_segment);
    this->updateBoundingBox(p_segment.getStart());
    this->updateBoundingBox(p_segment.getEnd());
}

auto LevelStorage::addSpecialArea(SpecialArea const & p_area) -> void
{
    m_special_areas.push_back(p_area);
    for(auto const & coordinate : p_area.getArea().getPolygon()) {
        this->updateBoundingBox(coordinate);
    }
}

auto LevelStorage::addAgent(Coordinate const & p_coordinate) -> void
{
    m_agents.emplace_back(Agent{p_coordinate});
    this->updateBoundingBox(p_coordinate);
}

auto LevelStorage::updateBoundingBox(const Coordinate & p_coordinate) -> void
{
    if(p_coordinate.x < m_bounding_box.lower_left.x) {
        m_bounding_box.lower_left.x = p_coordinate.x;
    } else if(p_coordinate.x > m_bounding_box.upper_right.x) {
        m_bounding_box.upper_right.x = p_coordinate.x;
    }

    if(p_coordinate.y < m_bounding_box.lower_left.y) {
        m_bounding_box.lower_left.y = p_coordinate.y;
    } else if(p_coordinate.y > m_bounding_box.upper_right.y) {
        m_bounding_box.upper_right.y = p_coordinate.y;
    }
}

} // namespace jps
