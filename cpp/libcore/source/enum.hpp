#include <type_traits>

template <typename T>
constexpr auto toUnderlying(const T & p_t) noexcept
{
    return static_cast<std::underlying_type_t<T>>(p_t);
}
