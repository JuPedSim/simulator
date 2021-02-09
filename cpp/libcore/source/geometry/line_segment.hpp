#pragma once

#include "geometry/coordinate.hpp"

#include <fmt/format.h>
#include <fmt/ostream.h>

namespace jps
{
class LineSegment
{
    Coordinate m_start;
    Coordinate m_end;

public:
    LineSegment(Coordinate p_start, Coordinate p_end);
    LineSegment(LineSegment const & p_other) = default;
    auto operator=(LineSegment const & p_other) -> LineSegment & = default;
    LineSegment(LineSegment && p_other)                          = default;
    auto operator=(LineSegment && p_other) -> LineSegment & = default;
    ~LineSegment()                                          = default;

    auto operator==(LineSegment const & p_other) const noexcept -> bool
    {
        // TODO are rotated line segments the same?
        return m_start == p_other.m_start && m_end == p_other.m_end;
    }
    auto operator!=(LineSegment const & p_other) const noexcept -> bool
    {
        return !(*this == p_other);
    }

    auto getStart() const -> Coordinate const & { return m_start; }

    auto getEnd() const -> Coordinate const & { return m_end; }

    auto rotate() -> void;
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
    auto format(const jps::LineSegment & p_line_segment, FormatContext & p_ctx)
    {
        return format_to(
            p_ctx.out(),
            "LINE_SEGMENT: ({}) -- ({})",
            p_line_segment.getStart(),
            p_line_segment.getEnd());
    };
};
} // namespace fmt
