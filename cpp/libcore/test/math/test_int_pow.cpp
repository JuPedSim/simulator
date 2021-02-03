
#include "math/int_pow.hpp"

#include <gtest/gtest.h>

TEST(intPow, BasicTests)
{
    EXPECT_EQ((jps ::math::intPow<10, 1>()), 10);
    EXPECT_EQ((jps ::math::intPow<10, 2>()), 100);
    EXPECT_EQ((jps ::math::intPow<2, 3>()), 8);
    EXPECT_EQ((jps ::math::intPow<0, 10>()), 0);
    EXPECT_EQ((jps ::math::intPow<100, 0>()), 1);
}
