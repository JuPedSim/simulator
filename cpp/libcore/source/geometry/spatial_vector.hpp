#pragma once

#include "geometry/length_unit.hpp"

#include <fmt/ostream.h>

namespace jps
{
/// Represents a directed vector in space
///
/// SpatialVectors origin is not the point of origin of coordinates [(0,0)].
/// It gives a direction in the plane and has no level.
class SpatialVector
{
    LengthUnit m_x;
    LengthUnit m_y;

public:
    SpatialVector(LengthUnit p_x, LengthUnit p_y) : m_x(p_x), m_y(p_y){};
    SpatialVector(SpatialVector const & p_other) = default;
    auto operator=(SpatialVector const & p_other) -> SpatialVector & = default;
    SpatialVector(SpatialVector && p_other)                          = default;
    auto operator=(SpatialVector && p_other) -> SpatialVector & = default;
    ~SpatialVector()                                            = default;

    auto operator==(SpatialVector const & p_other) const noexcept -> bool
    {
        return m_x == p_other.m_x && m_y == p_other.m_y;
    }
    auto operator!=(SpatialVector const & p_other) const noexcept -> bool
    {
        return !(*this == p_other);
    }

    auto x() const -> LengthUnit { return m_x; };
    auto x() -> LengthUnit & { return m_x; }

    auto y() const -> LengthUnit { return m_x; };
    auto y() -> LengthUnit & { return m_y; }
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
    auto format(const jps::SpatialVector & p_sv, FormatContext & p_ctx)
    {
        return format_to(p_ctx.out(), "SPATIAL_VECTOR ({}, {})", p_sv.x(), p_sv.y());
    }
};
} // namespace fmt