#include "geometry/coordinate.hpp"
#include "geometry/level.hpp"
#include "geometry/spatial_vector.hpp"

#include <gtest/gtest.h>
#include <tuple>

TEST(Coordinate, Constructors)
{
    using namespace jps;

    std::vector<std::tuple<LengthUnit, LengthUnit>> values{
        {10.32423_m, 213_mm},
        {-989.43854389_cm, 89123.0986_km},
        {124_um, 0.123_m},
        {565._cm, -1239.1_cm},
        {-167.32_m, -272.5_m}};

    std::vector<Coordinate> reference_values;

    // Simple constructor
    for(auto const & [x, y] : values) {
        Coordinate coordinate{x, y};
        EXPECT_EQ(coordinate.x, x);
        EXPECT_EQ(coordinate.y, y);
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
    EXPECT_TRUE((Coordinate{12_mm, 5.3_cm}) == (Coordinate{12_mm, 5.3_cm}));
    EXPECT_TRUE((Coordinate{60.345_m, -456.1_um}) == (Coordinate{60.345_m, -456.1_um}));
    EXPECT_TRUE((Coordinate{-909.1873_km, 5.3_mm}) == (Coordinate{-909.1873_km, 5.3_mm}));
    EXPECT_TRUE((Coordinate{-1632_cm, -55467.345_dm}) == (Coordinate{-1632_cm, -55467.345_dm}));
    EXPECT_TRUE((Coordinate{12_mm, 5.3_cm}) == (Coordinate{12_mm, 5.3_cm}));

    EXPECT_FALSE((Coordinate{12_mm, 5.3_cm}) == (Coordinate{-1232.1_m, 56.3_cm}));
    EXPECT_FALSE((Coordinate{60.345_m, -456.1_um}) == (Coordinate{-32.1_cm, -324.3_km}));
    EXPECT_FALSE((Coordinate{-909.1873_km, 5.3_mm}) == (Coordinate{8932.231_dm, -2346.32_m}));
    EXPECT_FALSE((Coordinate{-1632_cm, -55467.345_dm}) == (Coordinate{2.1_km, 56_mm}));
    EXPECT_FALSE((Coordinate{12_mm, 5.3_cm}) == (Coordinate{-1232.1_um, 56.3_cm}));

    // !=
    EXPECT_TRUE((Coordinate{12_mm, 5.3_cm}) != (Coordinate{-1232.1_m, 56.3_cm}));
    EXPECT_TRUE((Coordinate{60.345_m, -456.1_um}) != (Coordinate{-32.1_cm, -324.3_km}));
    EXPECT_TRUE((Coordinate{-909.1873_km, 5.3_mm}) != (Coordinate{8932.231_dm, -2346.32_m}));
    EXPECT_TRUE((Coordinate{-1632_cm, -55467.345_dm}) != (Coordinate{2.1_km, 56_mm}));
    EXPECT_TRUE((Coordinate{12_mm, 5.3_cm}) != (Coordinate{-1232.1_um, 56.3_cm}));

    EXPECT_FALSE((Coordinate{12_mm, 5.3_cm}) != (Coordinate{12_mm, 5.3_cm}));
    EXPECT_FALSE((Coordinate{60.345_m, -456.1_um}) != (Coordinate{60.345_m, -456.1_um}));
    EXPECT_FALSE((Coordinate{-909.1873_km, 5.3_mm}) != (Coordinate{-909.1873_km, 5.3_mm}));
    EXPECT_FALSE((Coordinate{-1632_cm, -55467.345_dm}) != (Coordinate{-1632_cm, -55467.345_dm}));
    EXPECT_FALSE((Coordinate{12_mm, 5.3_cm}) != (Coordinate{12_mm, 5.3_cm}));
}

TEST(CoordinateDisplace, DsiplacementWithZeroDoesNotChangeCoordinate)
{
    const auto expected          = jps::Coordinate(0_m, 0_m);
    const auto zero_displacement = jps::SpatialVector{0_m, 0_m};
    ASSERT_EQ(expected, expected + zero_displacement);
    ASSERT_EQ(expected, expected - zero_displacement);

    auto test_val = expected;
    test_val += zero_displacement;
    ASSERT_EQ(expected, test_val);

    test_val -= zero_displacement;
    ASSERT_EQ(expected, test_val);
}

TEST(CoordinateDisplace, PositiveDisplacementWorksWithSpatialVectorWithPositiveComponents)
{
    const auto base         = jps::Coordinate(6_m, 9_m);
    const auto expected     = jps::Coordinate(631_cm, 924_cm);
    const auto displacement = jps::SpatialVector{31_cm, 24_cm};
    ASSERT_EQ(expected, base + displacement);

    auto test_val = base;
    test_val += displacement;
    ASSERT_EQ(expected, test_val);
}

TEST(CoordinateDisplace, NegativeDisplacementWorksWithSpatialVectorWithPositiveComponents)
{
    const auto base         = jps::Coordinate(6_m, 9_m);
    const auto expected     = jps::Coordinate(569_cm, 876_cm);
    const auto displacement = jps::SpatialVector{31_cm, 24_cm};
    ASSERT_EQ(expected, base - displacement);

    auto test_val = base;
    test_val -= displacement;
    ASSERT_EQ(expected, test_val);
}

TEST(CoordinateDisplace, PositiveDisplacementWorksWithSpatialVectorWithNegativeComponents)
{
    const auto base         = jps::Coordinate(6_m, 9_m);
    const auto expected     = jps::Coordinate(569_cm, 876_cm);
    const auto displacement = jps::SpatialVector{-31_cm, -24_cm};
    ASSERT_EQ(expected, base + displacement);

    auto test_val = base;
    test_val += displacement;
    ASSERT_EQ(expected, test_val);
}

TEST(CoordinateDisplace, NegativeDisplacementWorksWithSpatialVectorWithNegativeComponents)
{
    const auto base         = jps::Coordinate(6_m, 9_m);
    const auto expected     = jps::Coordinate(631_cm, 924_cm);
    const auto displacement = jps::SpatialVector{-31_cm, -24_cm};
    ASSERT_EQ(expected, base - displacement);

    auto test_val = base;
    test_val -= displacement;
    ASSERT_EQ(expected, test_val);
}
