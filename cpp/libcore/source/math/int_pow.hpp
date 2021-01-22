#pragma once

#include <type_traits>

namespace jps::math
{
/// intPow() creates a lookup table for int base to the power of integral exponent
/// Must be used with non-type template parameters.
/// @tparam int base
/// @tparam exp exponent as unsigned short
template <int base, unsigned short exp>
constexpr auto intPow() -> int
{
    if constexpr(exp == 0) {
        return 1;
    } else {
        return base * intPow<base, exp - 1>();
    }
}
} // namespace jps::math
