#include "coordinate.hpp"

auto jps::Coordinate::operator==(const jps::Coordinate & p_other) const noexcept -> bool
{
    return m_x == p_other.m_x && m_y == p_other.m_y && m_lvl == p_other.m_lvl;
}

auto jps::Coordinate::operator!=(const jps::Coordinate & p_other) const noexcept -> bool
{
    return !(*this == p_other);
}
