#include "geometry/level.hpp"

#include <gtest/gtest.h>

TEST(Level, Constructors) // NOLINTLINE
{
    using namespace jps;

    std::vector<std::int32_t> reference_ids{10, -67, 123, 0, 832423, 123125, 9328345, -54682324};
    std::vector<Level> reference_values;

    // Simple constructor
    for(auto id : reference_ids) {
        Level level{id};
        EXPECT_EQ(level.id(), id);
        reference_values.emplace_back(level);
    }

    for(auto const & reference_value : reference_values) {
        // copy constructor
        Level copy_constructed{reference_value};
        EXPECT_EQ(reference_value, copy_constructed);

        // copy assignment operator
        Level copy_assigned = reference_value;
        EXPECT_EQ(reference_value, copy_assigned);

        // move constructor
        Level before_move_constructor{reference_value};
        Level move_constructed{std::move(before_move_constructor)}; // NOLINTLINE
        EXPECT_EQ(reference_value, move_constructed);

        // move assignment operator
        Level before_move_assigned{reference_value};
        Level move_assigned = std::move(before_move_assigned); // NOLINTLINE
        EXPECT_EQ(reference_value, move_assigned);
    }
}

TEST(Level, comparisonOperators) // NOLINTLINE
{
    using namespace jps;

    // ==
    EXPECT_TRUE(Level{10} == Level{10});
    EXPECT_TRUE(Level{123} == Level{123});
    EXPECT_TRUE(Level{0} == Level{0});
    EXPECT_TRUE(Level{1} == Level{1});
    EXPECT_TRUE(Level{-167567} == Level{-167567});
    EXPECT_TRUE(Level{-8932} == Level{-8932});
    EXPECT_TRUE(Level{124909412} == Level{124909412});
    EXPECT_FALSE(Level{10} == Level{-10});
    EXPECT_FALSE(Level{123} == Level{-123});
    EXPECT_FALSE(Level{0} == Level{345});
    EXPECT_FALSE(Level{1} == Level{34});
    EXPECT_FALSE(Level{124909412} == Level{0});

    // !=
    EXPECT_TRUE(Level{10} != Level{1123});
    EXPECT_TRUE(Level{-123} != Level{1});
    EXPECT_TRUE(Level{0} != Level{-345});
    EXPECT_TRUE(Level{1} != Level{34});
    EXPECT_TRUE(Level{124909412} != Level{0});
    EXPECT_FALSE(Level{10} != Level{10});
    EXPECT_FALSE(Level{-123} != Level{-123});
    EXPECT_FALSE(Level{0} != Level{0});
    EXPECT_FALSE(Level{1} != Level{1});
    EXPECT_FALSE(Level{124909412} != Level{124909412});
    EXPECT_FALSE(Level{-2345} != Level{-2345});
}
