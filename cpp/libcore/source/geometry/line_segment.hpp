#pragma once

#include "geometry/coordinate.hpp"

#include <fmt/format.h>
#include <fmt/ostream.h>

namespace jps
{
/// Represents a line segment defined by two end-points.
class LineSegment
{
    Coordinate m_start;
    Coordinate m_end;

public:
    LineSegment(Coordinate p_start, Coordinate p_end);

    auto operator==(LineSegment const & p_other) const noexcept -> bool
    {
        return (m_start == p_other.m_start && m_end == p_other.m_end) ||
               (m_start == p_other.m_end && m_end == p_other.m_start);
    }
    auto operator!=(LineSegment const & p_other) const noexcept -> bool
    {
        return !(*this == p_other);
    }

    auto getStart() const noexcept -> Coordinate const & { return m_start; }

    auto getEnd() const noexcept -> Coordinate const & { return m_end; }

    auto rotate() noexcept -> void;
};

} // namespace jps

namespace fmt
{
template <>
struct formatter<jps::LineSegment> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext & p_ctx)
    {
        return p_ctx.begin();
    }

    template <typename FormatContext>
    auto format(jps::LineSegment const & p_line_segment, FormatContext & p_ctx)
    {
        return format_to(
            p_ctx.out(),
            "LINE_SEGMENT: ({}) -- ({})",
            p_line_segment.getStart(),
            p_line_segment.getEnd());
    }
};
} // namespace fmt
