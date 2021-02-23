#include "geometry/coordinate.hpp"

#include <gtest/gtest.h>
#include <tuple>

TEST(Coordinate, Constructors)
{
    using namespace jps;

    std::vector<std::tuple<LengthUnit, LengthUnit, Level>> values{
        {10.32423_m, 213_mm, Level{21}},
        {-989.43854389_cm, 89123.0986_km, Level{1}},
        {124_um, 0.123_m, Level{-2}},
        {565._cm, -1239.1_cm, Level{21}},
        {-167.32_m, -272.5_m, Level{-19214}}};

    std::vector<Coordinate> reference_values;

    // Simple constructor
    for(auto const & [x, y, lvl] : values) {
        Coordinate coordinate{x, y, lvl};
        EXPECT_EQ(coordinate.x, x);
        EXPECT_EQ(coordinate.y, y);
        EXPECT_EQ(coordinate.lvl, lvl);
        reference_values.emplace_back(coordinate);
    }

    for(auto const & reference_value : reference_values) {
        // copy constructor
        Coordinate copy_constructed{reference_value};
        EXPECT_EQ(reference_value, copy_constructed);

        // copy assignment operator
        Coordinate copy_assigned = reference_value;
        EXPECT_EQ(reference_value, copy_assigned);

        // move constructor
        Coordinate before_move_constructor{reference_value};
        Coordinate move_constructed{std::move(before_move_constructor)};
        EXPECT_EQ(reference_value, move_constructed);

        // move assignment operator
        Coordinate before_move_assigned{reference_value};
        Coordinate move_assigned = std::move(before_move_assigned);
        EXPECT_EQ(reference_value, move_assigned);
    }
}

TEST(Coordinate, comparisonOperators)
{
    using namespace jps;

    // ==
    EXPECT_TRUE((Coordinate{12_mm, 5.3_cm, Level{12}}) == (Coordinate{12_mm, 5.3_cm, Level{12}}));
    EXPECT_TRUE(
        (Coordinate{60.345_m, -456.1_um, Level{-2}}) ==
        (Coordinate{60.345_m, -456.1_um, Level{-2}}));
    EXPECT_TRUE(
        (Coordinate{-909.1873_km, 5.3_mm, Level{6}}) ==
        (Coordinate{-909.1873_km, 5.3_mm, Level{6}}));
    EXPECT_TRUE(
        (Coordinate{-1632_cm, -55467.345_dm, Level{67}}) ==
        (Coordinate{-1632_cm, -55467.345_dm, Level{67}}));
    EXPECT_TRUE((Coordinate{12_mm, 5.3_cm, Level{12}}) == (Coordinate{12_mm, 5.3_cm, Level{12}}));

    EXPECT_FALSE(
        (Coordinate{12_mm, 5.3_cm, Level{12}}) == (Coordinate{-1232.1_m, 56.3_cm, Level{2}}));
    EXPECT_FALSE(
        (Coordinate{60.345_m, -456.1_um, Level{-2}}) ==
        (Coordinate{-32.1_cm, -324.3_km, Level{-2}}));
    EXPECT_FALSE(
        (Coordinate{-909.1873_km, 5.3_mm, Level{6}}) ==
        (Coordinate{8932.231_dm, -2346.32_m, Level{12}}));
    EXPECT_FALSE(
        (Coordinate{-1632_cm, -55467.345_dm, Level{67}}) ==
        (Coordinate{2.1_km, 56_mm, Level{267}}));
    EXPECT_FALSE(
        (Coordinate{12_mm, 5.3_cm, Level{12}}) == (Coordinate{-1232.1_um, 56.3_cm, Level{-29}}));

    // !=
    EXPECT_TRUE(
        (Coordinate{12_mm, 5.3_cm, Level{12}}) != (Coordinate{-1232.1_m, 56.3_cm, Level{2}}));
    EXPECT_TRUE(
        (Coordinate{60.345_m, -456.1_um, Level{-2}}) !=
        (Coordinate{-32.1_cm, -324.3_km, Level{-2}}));
    EXPECT_TRUE(
        (Coordinate{-909.1873_km, 5.3_mm, Level{6}}) !=
        (Coordinate{8932.231_dm, -2346.32_m, Level{12}}));
    EXPECT_TRUE(
        (Coordinate{-1632_cm, -55467.345_dm, Level{67}}) !=
        (Coordinate{2.1_km, 56_mm, Level{267}}));
    EXPECT_TRUE(
        (Coordinate{12_mm, 5.3_cm, Level{12}}) != (Coordinate{-1232.1_um, 56.3_cm, Level{-29}}));

    EXPECT_FALSE((Coordinate{12_mm, 5.3_cm, Level{12}}) != (Coordinate{12_mm, 5.3_cm, Level{12}}));
    EXPECT_FALSE(
        (Coordinate{60.345_m, -456.1_um, Level{-2}}) !=
        (Coordinate{60.345_m, -456.1_um, Level{-2}}));
    EXPECT_FALSE(
        (Coordinate{-909.1873_km, 5.3_mm, Level{6}}) !=
        (Coordinate{-909.1873_km, 5.3_mm, Level{6}}));
    EXPECT_FALSE(
        (Coordinate{-1632_cm, -55467.345_dm, Level{67}}) !=
        (Coordinate{-1632_cm, -55467.345_dm, Level{67}}));
    EXPECT_FALSE((Coordinate{12_mm, 5.3_cm, Level{12}}) != (Coordinate{12_mm, 5.3_cm, Level{12}}));
}
