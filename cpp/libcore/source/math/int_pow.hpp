#pragma once

#include <type_traits>

namespace jps::math
{
/// intPow() creates a lookup table for integral base to the power of integral exponent
/// Must be used with non-type template parameters.
/// @tparam T underlying integral type.
/// @tparam base must be of integral type T
/// @tparam exp exponent as unsigned short
template <typename T, T base, unsigned short exp>
constexpr T intPow()
{
    static_assert(std::is_integral<T>(), "intPow() underlying type must be integral.");

    if constexpr(exp == 0) {
        return 1;
    } else {
        return base * intPow<T, base, exp - 1>();
    }
}
} // namespace jps::math
