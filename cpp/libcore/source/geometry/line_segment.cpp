#include "line_segment.hpp"

#include <fmt/format.h>
#include <stdexcept>

jps::LineSegment::LineSegment(jps::Coordinate p_start, jps::Coordinate p_end) :
    m_start(p_start), m_end(p_end)
{
    // start and end point need to be in same level
    if(p_start.lvl() != p_end.lvl()) {
        throw std::invalid_argument(fmt::format(
            FMT_STRING("For constructing LineSegment start and end need to be on same level. But "
                       "are {} and {}"),
            p_start.lvl(),
            p_end.lvl()));
    }

    // start and end point need to be different
    if(p_start == p_end) {
        throw std::invalid_argument(fmt::format(
            FMT_STRING("For constructing LineSegment start and end need to be different. But are "
                       "{} and {}."),
            p_start,
            p_end));
    }
}

auto jps::LineSegment::rotate() -> void
{
    auto tmp = m_start;
    m_start  = m_end;
    m_end    = tmp;
}
