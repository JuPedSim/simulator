#pragma once

#include "geometry/length_unit.hpp"
#include "geometry/level.hpp"

#include <fmt/ostream.h>

namespace jps
{
/// Represents a spatial coordinate in the world (geometry).
struct Coordinate {
    LengthUnit m_x; // NOLINTLINE
    LengthUnit m_y; // NOLINTLINE
    Level m_lvl;    // NOLINTLINE

public:
    Coordinate(LengthUnit p_x, LengthUnit p_y, Level p_lvl) : m_x(p_x), m_y(p_y), m_lvl(p_lvl){};

    auto operator==(Coordinate const & p_other) const noexcept -> bool;
    auto operator!=(Coordinate const & p_other) const noexcept -> bool;
};
} // namespace jps


namespace fmt
{
template <>
struct formatter<jps::Coordinate> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext & p_ctx)
    {
        return p_ctx.begin();
    }

    template <typename FormatContext>
    auto format(jps::Coordinate const & p_coordinate, FormatContext & p_ctx)
    {
        return format_to(
            p_ctx.out(),
            "COORDINATE: ({}, {}) -- {}",
            p_coordinate.m_x,
            p_coordinate.m_y,
            p_coordinate.m_lvl);
    }
};
} // namespace fmt
