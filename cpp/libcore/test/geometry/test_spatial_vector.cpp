#include "geometry/spatial_vector.hpp"

#include <cmath>
#include <gtest/gtest.h>

TEST(SpatialVector, Constructors)
{
    using namespace jps;

    std::vector<std::tuple<LengthUnit, LengthUnit>> values{
        {17.44_m, 7.3_mm},
        {-989.43_km, 5438.9_cm},
        {1224_um, -0.123_m},
        {1545._cm, 12.112_cm},
        {-167.32_m, -272.5_m}};

    std::vector<SpatialVector> reference_values;

    // Simple constructor
    for(auto const & [x, y] : values) {
        SpatialVector spatial_vector{x, y};
        EXPECT_EQ(spatial_vector.x, x);
        EXPECT_EQ(spatial_vector.y, y);
        reference_values.emplace_back(spatial_vector);
    }

    for(auto const & reference_value : reference_values) {
        // copy constructor
        SpatialVector copy_constructed{reference_value};
        EXPECT_EQ(reference_value, copy_constructed);

        // copy assignment operator
        SpatialVector copy_assigned = reference_value;
        EXPECT_EQ(reference_value, copy_assigned);

        // move constructor
        SpatialVector before_move_constructor{reference_value};
        SpatialVector move_constructed{std::move(before_move_constructor)};
        EXPECT_EQ(reference_value, move_constructed);

        // move assignment operator
        SpatialVector before_move_assigned{reference_value};
        SpatialVector move_assigned = std::move(before_move_assigned);
        EXPECT_EQ(reference_value, move_assigned);
    }
}

TEST(SpatialVector, comparisonOperators)
{
    using namespace jps;

    // ==
    EXPECT_TRUE((SpatialVector{1.4_mm, 7.3_cm}) == (SpatialVector{1.4_mm, 7.3_cm}));
    EXPECT_TRUE((SpatialVector{45.75_m, -956.14_um}) == (SpatialVector{45.75_m, -956.14_um}));
    EXPECT_TRUE((SpatialVector{-4.183_km, 245.3_mm}) == (SpatialVector{-4.183_km, 245.3_mm}));
    EXPECT_TRUE((SpatialVector{-132_dm, -56.451_dm}) == (SpatialVector{-132_dm, -56.451_dm}));
    EXPECT_TRUE((SpatialVector{1.2_mm, 53_cm}) == (SpatialVector{1.2_mm, 53_cm}));

    EXPECT_FALSE((SpatialVector{122_mm, 5.7_cm}) == (SpatialVector{-1232.1_m, 56.3_cm}));
    EXPECT_FALSE((SpatialVector{60.45_m, -45.66_um}) == (SpatialVector{-32.1_cm, -324.3_km}));
    EXPECT_FALSE((SpatialVector{-909.183_km, 5.3_mm}) == (SpatialVector{8932.231_dm, -2346.32_m}));
    EXPECT_FALSE((SpatialVector{-19132_cm, -557.345_dm}) == (SpatialVector{2.1_km, 56_mm}));
    EXPECT_FALSE((SpatialVector{142_mm, 5.3_cm}) == (SpatialVector{-1232.1_um, 56.3_cm}));

    // !=
    EXPECT_TRUE((SpatialVector{12_mm, 5.3_cm}) != (SpatialVector{-1232.1_m, 56.3_cm}));
    EXPECT_TRUE((SpatialVector{60.345_m, -456.1_um}) != (SpatialVector{-32.1_cm, -324.3_km}));
    EXPECT_TRUE((SpatialVector{-909.1873_km, 5.3_mm}) != (SpatialVector{8932.231_dm, -2346.32_m}));
    EXPECT_TRUE((SpatialVector{-1632_cm, -55467.345_dm}) != (SpatialVector{2.1_km, 56_mm}));
    EXPECT_TRUE((SpatialVector{12_mm, 5.3_cm}) != (SpatialVector{-1232.1_um, 56.3_cm}));

    EXPECT_FALSE((SpatialVector{12_mm, 5.3_cm}) != (SpatialVector{12_mm, 5.3_cm}));
    EXPECT_FALSE((SpatialVector{60.345_m, -456.1_um}) != (SpatialVector{60.345_m, -456.1_um}));
    EXPECT_FALSE((SpatialVector{-909.1873_km, 5.3_mm}) != (SpatialVector{-909.1873_km, 5.3_mm}));
    EXPECT_FALSE((SpatialVector{-1632_cm, -554.345_dm}) != (SpatialVector{-1632_cm, -554.345_dm}));
    EXPECT_FALSE((SpatialVector{12_mm, 5.3_cm}) != (SpatialVector{12_mm, 5.3_cm}));
}
