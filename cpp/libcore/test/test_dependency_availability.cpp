#include <fmt/format.h>
#include <gtest/gtest.h>
#include <string_view>

TEST(Fmt, IsAvailable)
{
    constexpr std::string_view expected = "a <-> b";
    const auto formatted_string         = fmt::format("{} <-> {}", 'a', 'b');
    ASSERT_EQ(formatted_string, expected);
}
