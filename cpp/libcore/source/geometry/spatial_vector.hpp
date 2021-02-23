#pragma once

#include "geometry/length_unit.hpp"

#include <fmt/ostream.h>

namespace jps
{
/// Represents a directed vector in space
///
/// SpatialVectors origin is not the point of origin of coordinates [(0,0)].
/// It gives a direction in the plane and has no level.
struct SpatialVector {
    LengthUnit x; // NOLINTLINE
    LengthUnit y; // NOLINTLINE

public:
    SpatialVector(LengthUnit p_x, LengthUnit p_y) : x(p_x), y(p_y){};

    auto operator==(SpatialVector const & p_other) const noexcept -> bool
    {
        return x == p_other.x && y == p_other.y;
    }
    auto operator!=(SpatialVector const & p_other) const noexcept -> bool
    {
        return !(*this == p_other);
    }
};
} // namespace jps

namespace fmt
{
template <>
struct formatter<jps::SpatialVector> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext & p_ctx)
    {
        return p_ctx.begin();
    }

    template <typename FormatContext>
    auto format(jps::SpatialVector const & p_sv, FormatContext & p_ctx)
    {
        return format_to(p_ctx.out(), "SPATIAL_VECTOR ({}, {})", p_sv.x, p_sv.y);
    }
};
} // namespace fmt