
#include "math/int_pow.hpp"

#include <gtest/gtest.h>

TEST(intPow, BasicTests)
{
    EXPECT_EQ((jps ::math::intPow<int, 10, 1>()), 10);
    EXPECT_EQ((jps ::math::intPow<int, 10, 2>()), 100);
    EXPECT_EQ((jps ::math::intPow<int, 2, 3>()), 8);
    EXPECT_EQ((jps ::math::intPow<int, 0, 10>()), 0);
    EXPECT_EQ((jps ::math::intPow<int, 100, 0>()), 1);
}
