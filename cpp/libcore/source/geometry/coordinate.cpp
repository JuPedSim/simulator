#include "coordinate.hpp"

namespace jps
{
auto Coordinate::operator==(const jps::Coordinate & p_other) const noexcept -> bool
{
    return x == p_other.x && y == p_other.y && lvl == p_other.lvl;
}

auto Coordinate::operator!=(const jps::Coordinate & p_other) const noexcept -> bool
{
    return !(*this == p_other);
}

auto Coordinate::operator+(SpatialVector const & p_displacement) const noexcept -> Coordinate
{
    return {this->x + p_displacement.x, this->y + p_displacement.y, this->lvl};
}

auto Coordinate::operator-(SpatialVector const & p_displacement) const noexcept -> Coordinate
{
    return {this->x - p_displacement.x, this->y - p_displacement.y, this->lvl};
}

auto Coordinate::operator+=(SpatialVector const & p_displacement) noexcept -> Coordinate &
{
    this->x += p_displacement.x;
    this->y += p_displacement.y;
    return *this;
}

auto Coordinate::operator-=(SpatialVector const & p_displacement) noexcept -> Coordinate &
{
    this->x -= p_displacement.x;
    this->y -= p_displacement.y;
    return *this;
}


} // namespace jps
