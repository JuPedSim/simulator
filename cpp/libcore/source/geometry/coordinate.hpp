#pragma once

#include "geometry/length_unit.hpp"
#include "geometry/level.hpp"

#include <fmt/ostream.h>

namespace jps
{
/// Represents a spatial coordinate in the world (geometry).
struct Coordinate {
    LengthUnit x; // NOLINTLINE
    LengthUnit y; // NOLINTLINE
    Level lvl;    // NOLINTLINE

public:
    Coordinate(LengthUnit p_x, LengthUnit p_y, Level p_lvl) : x(p_x), y(p_y), lvl(p_lvl){};

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
            p_coordinate.x,
            p_coordinate.y,
            p_coordinate.lvl);
    }
};
} // namespace fmt
