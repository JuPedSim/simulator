#include "world.hpp"

#include "geometry/level_storage.hpp"
#include "util/jpsexception.hpp"

namespace jps
{
auto World::addLineSegment(const Level & p_level, const LineSegment & p_segment) -> void
{
    m_level_to_level_storage.at(p_level).m_line_segments.push_back(p_segment);
}

auto World::addSpecialArea(const Level & p_level, const SpecialArea & p_area) -> void
{
    m_level_to_level_storage.at(p_level).m_special_areas.push_back(p_area);
}


auto World::addLevel(Level const & p_level) -> LevelStorage &
{
    if(m_level_to_level_storage.find(p_level) != m_level_to_level_storage.end()) {
        throw JPSGeometryException(
            fmt::format(FMT_STRING("Trying to add Level {} which already exists."), p_level));
    }
    return m_level_to_level_storage[p_level];
}
auto World::getLevel(Level const & p_level) -> LevelStorage &
{
    return m_level_to_level_storage.at(p_level);
}
auto World::getLevel(Level const & p_level) const -> LevelStorage const &
{
    return m_level_to_level_storage.at(p_level);
}
} // namespace jps
