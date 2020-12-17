#pragma once

#include "enum.hpp"
#include "math/int_pow.hpp"

#include <cstdint>
#include <type_traits>

namespace jps
{
/// Enumeration for supported length units.
/// Underlying integer must be set to the decimal exponent relative to meter (like SI).
enum class Units { mum = -6, mm = -3, cm = -2, dm = -1, m = 0, km = 3 };
const int DECIMAL_BASE = 10;

namespace details
{
/// Scales the given quantity of a length unit from `from` unit to `to` unit.
/// The used  quantity type T can be deduced automatically.
/// If from < to the quantity is divided and truncated towards zero for integral T.
/// Integer overflow is not checked.
/// Can be called like: `scaleQuantity<Units::mm, Units::cm>(10)`
/// @tparam T should be of integral type
template <Units from, Units to, typename T>
constexpr T scaleQuantity(T p_quantity)
{
    static_assert(std::is_integral_v<T>, "T in scaleQuantity() should be of integral type.");

    const int diff_exp = toUnderlying(from) - toUnderlying(to);

    if constexpr(diff_exp < 0) {
        return p_quantity / jps::math::intPow<T, DECIMAL_BASE, -diff_exp>();
    } else {
        return p_quantity * jps::math::intPow<T, DECIMAL_BASE, diff_exp>();
    }
}
} // namespace details
} // namespace jps
