#include "coordinate.hpp"

auto jps::Coordinate::operator==(const jps::Coordinate & p_other) const noexcept -> bool
{
    return x == p_other.x && y == p_other.y && lvl == p_other.lvl;
}

auto jps::Coordinate::operator!=(const jps::Coordinate & p_other) const noexcept -> bool
{
    return !(*this == p_other);
}
