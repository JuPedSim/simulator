#include "level_storage.hpp"

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
    // TODO (kkz) This can be changed to
    // m_agents.emplace_back(p_coordinate);
    // but requires C++20 to fix the missing aggregate initializaition from paretheses
    // otherwise we have to provide a CTOR to the struct
    m_agents.push_back({p_coordinate});
}

} // namespace jps
