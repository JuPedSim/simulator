#include "geometry/coordinate.hpp"

#include <gtest/gtest.h>
#include <tuple>

TEST(Coordinate, Constructors) // NOLINTLINE
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
        EXPECT_EQ(coordinate.x(), x);
        EXPECT_EQ(coordinate.y(), y);
        EXPECT_EQ(coordinate.lvl(), lvl);
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
        Coordinate move_constructed{std::move(before_move_constructor)}; // NOLINTLINE
        EXPECT_EQ(reference_value, move_constructed);

        // move assignment operator
        Coordinate before_move_assigned{reference_value};
        Coordinate move_assigned = std::move(before_move_assigned); // NOLINTLINE
        EXPECT_EQ(reference_value, move_assigned);
    }
}

TEST(Coordinate, comparisonOperators) // NOLINTLINE
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

TEST(Coordinate, setters) // NOLINTLINE
{
    using namespace jps;
    Coordinate coordinate{120.12_mm, 21312._m, Level{213}};

    // Setting x value
    LengthUnit new_x = 9324.123_m;
    coordinate.x()   = new_x;
    EXPECT_EQ(coordinate.x(), new_x);
    {
        const Coordinate & const_coordinate = coordinate;
        EXPECT_EQ(const_coordinate.x(), new_x);
    }

    new_x          = -123.67_km;
    coordinate.x() = new_x;
    EXPECT_EQ(coordinate.x(), new_x);

    new_x          = 324234932_um;
    coordinate.x() = new_x;
    EXPECT_EQ(coordinate.x(), new_x);
    {
        const Coordinate & const_coordinate = coordinate;
        EXPECT_EQ(const_coordinate.x(), new_x);
    }

    new_x          = -843543.435_um;
    coordinate.x() = new_x;
    EXPECT_EQ(coordinate.x(), new_x);
    {
        const Coordinate & const_coordinate = coordinate;
        EXPECT_EQ(const_coordinate.x(), new_x);
    }

    new_x          = 0.912_m;
    coordinate.x() = new_x;
    EXPECT_EQ(coordinate.x(), new_x);
    {
        const Coordinate & const_coordinate = coordinate;
        EXPECT_EQ(const_coordinate.x(), new_x);
    }

    // Setting y value
    LengthUnit new_y = 94.653_m;
    coordinate.y()   = new_y;
    EXPECT_EQ(coordinate.y(), new_y);
    {
        const Coordinate & const_coordinate = coordinate;
        EXPECT_EQ(const_coordinate.y(), new_y);
    }

    new_y          = -234.78_km;
    coordinate.y() = new_y;
    EXPECT_EQ(coordinate.y(), new_y);
    {
        const Coordinate & const_coordinate = coordinate;
        EXPECT_EQ(const_coordinate.y(), new_y);
    }

    new_y          = 23_um;
    coordinate.y() = new_y;
    EXPECT_EQ(coordinate.y(), new_y);
    {
        const Coordinate & const_coordinate = coordinate;
        EXPECT_EQ(const_coordinate.y(), new_y);
    }

    new_y          = 576.238_um;
    coordinate.y() = new_y;
    EXPECT_EQ(coordinate.y(), new_y);
    {
        const Coordinate & const_coordinate = coordinate;
        EXPECT_EQ(const_coordinate.y(), new_y);
    }

    new_y          = 0.912_m;
    coordinate.y() = new_y;
    EXPECT_EQ(coordinate.y(), new_y);
    {
        const Coordinate & const_coordinate = coordinate;
        EXPECT_EQ(const_coordinate.y(), new_y);
    }

    // Setting lvl value
    Level new_lvl_0{-54};
    coordinate.lvl() = new_lvl_0;
    EXPECT_EQ(coordinate.lvl(), new_lvl_0);
    {
        const Coordinate & const_coordinate = coordinate;
        EXPECT_EQ(const_coordinate.lvl(), new_lvl_0);
    }

    Level new_lvl_1{-4};
    coordinate.lvl() = new_lvl_1;
    EXPECT_EQ(coordinate.lvl(), new_lvl_1);
    {
        const Coordinate & const_coordinate = coordinate;
        EXPECT_EQ(const_coordinate.lvl(), new_lvl_1);
    }

    Level new_lvl_2{0};
    coordinate.lvl() = new_lvl_2;
    EXPECT_EQ(coordinate.lvl(), new_lvl_2);
    {
        const Coordinate & const_coordinate = coordinate;
        EXPECT_EQ(const_coordinate.lvl(), new_lvl_2);
    }

    Level new_lvl_3{18};
    coordinate.lvl() = new_lvl_3;
    EXPECT_EQ(coordinate.lvl(), new_lvl_3);
    {
        const Coordinate & const_coordinate = coordinate;
        EXPECT_EQ(const_coordinate.lvl(), new_lvl_3);
    }

    Level new_lvl_4{41};
    coordinate.lvl() = new_lvl_4;
    EXPECT_EQ(coordinate.lvl(), new_lvl_4);
    {
        const Coordinate & const_coordinate = coordinate;
        EXPECT_EQ(const_coordinate.lvl(), new_lvl_4);
    }
}