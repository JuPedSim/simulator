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
} // namespace jps
