#include "line_segment.hpp"

#include "util/jpsexception.hpp"

#include <fmt/format.h>
#include <stdexcept>

jps::LineSegment::LineSegment(jps::Coordinate p_start, jps::Coordinate p_end) :
    m_start(p_start), m_end(p_end)
{
    // start and end point need to be different
    if(p_start == p_end) {
        throw JPSGeometryException(fmt::format(
            FMT_STRING("For constructing LineSegment start and end need to be different. But are "
                       "{} and {}."),
            p_start,
            p_end));
    }
}

auto jps::LineSegment::rotate() noexcept -> void
{
    std::swap(m_start, m_end);
}
