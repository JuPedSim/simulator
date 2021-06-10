#include "geometry/line_segment.hpp"
#include "util/jpsexception.hpp"

#include <cmath>
#include <gtest/gtest.h>

TEST(LineSegment, Constructor)
{
    using namespace jps;

    // Successful construction
    std::vector<std::pair<Coordinate, Coordinate>> values{
        {{10.32423_m, 213_mm}, {21._cm, 902_um}},
        {{-989.43854389_cm, 89123.0986_km}, {21.3_m, 9_cm}},
        {{124_um, 0.123_m}, {-12_um, 21.01_km}},
        {{565._cm, -1239.1_cm}, {94.3_cm, 8.54_cm}},
        {{-167.32_m, -272.5_m}, {-0.111_mm, -11.90_um}}};

    std::vector<LineSegment> reference_values;

    // Simple constructor
    for(auto const & [start, end] : values) {
        LineSegment line_segment{start, end};
        EXPECT_EQ(line_segment.getStart(), start);
        EXPECT_EQ(line_segment.getEnd(), end);
        reference_values.emplace_back(line_segment);
    }

    for(auto const & reference_value : reference_values) {
        // copy constructor
        LineSegment copy_constructed{reference_value};
        EXPECT_EQ(reference_value, copy_constructed);

        // copy assignment operator
        LineSegment copy_assigned = reference_value;
        EXPECT_EQ(reference_value, copy_assigned);

        // move constructor
        LineSegment before_move_constructor{reference_value};
        LineSegment move_constructed{std::move(before_move_constructor)};
        EXPECT_EQ(reference_value, move_constructed);

        // move assignment operator
        LineSegment before_move_assigned{reference_value};
        LineSegment move_assigned = std::move(before_move_assigned);
        EXPECT_EQ(reference_value, move_assigned);
    }

    // Failing constructors
    // Start and end point not different
    EXPECT_THROW((LineSegment{{-12.1_m, 93_m}, {-12.1_m, 93_m}}), JPSGeometryException);
    EXPECT_THROW((LineSegment{{990_mm, 0.1_dm}, {990_mm, 0.1_dm}}), JPSGeometryException);
    EXPECT_THROW((LineSegment{{-51.5_cm, -1.68_cm}, {-51.5_cm, -1.68_cm}}), JPSGeometryException);
}

TEST(LineSegment, comparisonOperators)
{
    using namespace jps;

    // ==
    EXPECT_TRUE(
        (LineSegment{{10.32423_m, 213_mm}, {21._cm, 902_um}}) ==
        (LineSegment{{10.32423_m, 213_mm}, {21._cm, 902_um}}));
    EXPECT_TRUE(
        (LineSegment{{-989.43854389_cm, 89123.0986_km}, {21.3_m, 9_cm}}) ==
        (LineSegment{{-989.43854389_cm, 89123.0986_km}, {21.3_m, 9_cm}}));
    EXPECT_TRUE(
        (LineSegment{{124_um, 0.123_m}, {-12_um, 21.01_km}}) ==
        (LineSegment{{124_um, 0.123_m}, {-12_um, 21.01_km}}));
    EXPECT_TRUE(
        (LineSegment{{565._cm, -1239.1_cm}, {94.3_cm, 8.54_cm}}) ==
        (LineSegment{{565._cm, -1239.1_cm}, {94.3_cm, 8.54_cm}}));
    EXPECT_TRUE(
        (LineSegment{{0.0_m, 1_m}, {0_m, 1.1_m}}) == (LineSegment{{0_m, 1.1_m}, {0_m, 1_m}}));
    EXPECT_TRUE(
        (LineSegment{{565._cm, -1239.1_cm}, {94.3_cm, 8.54_cm}}) ==
        (LineSegment{{94.3_cm, 8.54_cm}, {565._cm, -1239.1_cm}}));
    EXPECT_TRUE(
        (LineSegment{{0.0_m, 1_m}, {0_m, 1.1_m}}) == (LineSegment{{0_m, 1.1_m}, {0_m, 1_m}}));

    EXPECT_FALSE(
        (LineSegment{{-12.1_m, 93_m}, {-12.1_m, 123_m}}) ==
        (LineSegment{{-167.32_m, -272.5_m}, {-0.111_mm, -11.90_um}}));
    EXPECT_FALSE(
        (LineSegment{{-12.1_m, 93_m}, {-12.1_m, 123_m}}) ==
        (LineSegment{{-12.1_m, 94_m}, {-12.1_m, 123_m}}));
    EXPECT_FALSE(
        (LineSegment{{-09.1_m, 7_m}, {-3.1_m, 2_m}}) ==
        (LineSegment{{-6.32_m, -65.5_m}, {-0.123_mm, -12.2_um}}));

    // !=
    EXPECT_TRUE(
        (LineSegment{{-12.1_m, 93_m}, {-12.1_m, 123_m}}) !=
        (LineSegment{{-167.32_m, -272.5_m}, {-0.111_mm, -11.90_um}}));
    EXPECT_TRUE(
        (LineSegment{{-12.1_m, 93_m}, {-12.1_m, 123_m}}) !=
        (LineSegment{{-12.1_m, 94_m}, {-12.1_m, 123_m}}));
    EXPECT_TRUE(
        (LineSegment{{-09.1_m, 7_m}, {-3.1_m, 2_m}}) !=
        (LineSegment{{-6.32_m, -65.5_m}, {-0.123_mm, -12.2_um}}));

    EXPECT_FALSE(
        (LineSegment{{0.0_m, 1_m}, {0_m, 1.1_m}}) != (LineSegment{{0_m, 1.1_m}, {0_m, 1_m}}));
    EXPECT_FALSE(
        (LineSegment{{10.32423_m, 213_mm}, {21._cm, 902_um}}) !=
        (LineSegment{{10.32423_m, 213_mm}, {21._cm, 902_um}}));
    EXPECT_FALSE(
        (LineSegment{{-989.43854389_cm, 89123.0986_km}, {21.3_m, 9_cm}}) !=
        (LineSegment{{-989.43854389_cm, 89123.0986_km}, {21.3_m, 9_cm}}));
    EXPECT_FALSE(
        (LineSegment{{124_um, 0.123_m}, {-12_um, 21.01_km}}) !=
        (LineSegment{{124_um, 0.123_m}, {-12_um, 21.01_km}}));
    EXPECT_FALSE(
        (LineSegment{{565._cm, -1239.1_cm}, {94.3_cm, 8.54_cm}}) !=
        (LineSegment{{565._cm, -1239.1_cm}, {94.3_cm, 8.54_cm}}));
    EXPECT_FALSE(
        (LineSegment{{-167.32_m, -272.5_m}, {-0.111_mm, -11.90_um}}) !=
        (LineSegment{{-167.32_m, -272.5_m}, {-0.111_mm, -11.90_um}}));
}

TEST(LineSegment, rotate)
{
    using namespace jps;
    std::vector<LineSegment> line_segments{
        {{10.32423_m, 213_mm}, {21._cm, 902_um}},
        {{-989.43854389_cm, 89123.0986_km}, {21.3_m, 9_cm}},
        {{124_um, 0.123_m}, {-12_um, 21.01_km}},
        {{565._cm, -1239.1_cm}, {94.3_cm, 8.54_cm}},
        {{-167.32_m, -272.5_m}, {-0.111_mm, -11.90_um}}};

    for(auto line_segment : line_segments) {
        LineSegment rotated = line_segment;
        rotated.rotate();

        EXPECT_TRUE(rotated.getStart() == line_segment.getEnd());
        EXPECT_TRUE(rotated.getEnd() == line_segment.getStart());
    }
}
