#pragma once

#include "geometry/length_unit.hpp"
#include "geometry/level.hpp"

#include <fmt/ostream.h>

namespace jps
{
/// Spatial Coordinate
///
/// Represents a spatial coordinate in the world (geometry).
class Coordinate
{
    LengthUnit m_x;
    LengthUnit m_y;
    Level m_lvl;

public:
    Coordinate(LengthUnit p_x, LengthUnit p_y, Level p_lvl) : m_x(p_x), m_y(p_y), m_lvl(p_lvl){};
    Coordinate(Coordinate const & p_other) = default;
    auto operator=(Coordinate const & p_other) -> Coordinate & = default;
    Coordinate(Coordinate && p_other)                          = default;
    auto operator=(Coordinate && p_other) -> Coordinate & = default;
    ~Coordinate()                                         = default;

    auto operator==(Coordinate const & p_other) const noexcept -> bool;
    auto operator!=(Coordinate const & p_other) const noexcept -> bool;

    auto x() const -> LengthUnit { return m_x; };
    auto x() -> LengthUnit & { return m_x; }

    auto y() const -> LengthUnit { return m_y; };
    auto y() -> LengthUnit & { return m_y; }

    auto lvl() const -> Level { return m_lvl; }
    auto lvl() -> Level & { return m_lvl; }
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
    auto format(const jps::Coordinate & p_coordinate, FormatContext & p_ctx)
    {
        return format_to(
            p_ctx.out(),
            "COORDINATE: ({}, {}) -- {}",
            p_coordinate.x(),
            p_coordinate.y(),
            p_coordinate.lvl());
    }
};
} // namespace fmt
