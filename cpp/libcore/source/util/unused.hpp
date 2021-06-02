#pragma once

namespace jps
{
/// Helper function to silence unused parameter warning.
///
/// This method can be used with all unused parameters as parameter to silence the compiler warning.
template <typename... Ts>
// NOLINTNEXTLINE
void unused(Ts &&...)
{
}
} // namespace jps
