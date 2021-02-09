#include "geometry/line_segment.hpp"

#include <cmath>
#include <gtest/gtest.h>

// NOLINTNEXTLINE
TEST(LineSegment, Constructor)
{
    using namespace jps;

    // Successful construction
    std::vector<std::pair<Coordinate, Coordinate>> values{
        {{10.32423_m, 213_mm, Level{21}}, {21._cm, 902_um, Level{21}}},
        {{-989.43854389_cm, 89123.0986_km, Level{1}}, {21.3_m, 9_cm, Level{1}}},
        {{124_um, 0.123_m, Level{-2}}, {-12_um, 21.01_km, Level{-2}}},
        {{565._cm, -1239.1_cm, Level{21}}, {94.3_cm, 8.54_cm, Level{21}}},
        {{-167.32_m, -272.5_m, Level{-19214}}, {-0.111_mm, -11.90_um, Level{-19214}}}};

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
        LineSegment move_constructed{std::move(before_move_constructor)}; // NOLINTLINE
        EXPECT_EQ(reference_value, move_constructed);

        // move assignment operator
        LineSegment before_move_assigned{reference_value};
        LineSegment move_assigned = std::move(before_move_assigned); // NOLINTLINE
        EXPECT_EQ(reference_value, move_assigned);
    }

    // Failing constructors
    // Start and end not on same level
    // NOLINTNEXTLINE
    EXPECT_THROW(
        (LineSegment{{-12.1_m, 93_m, Level{21}}, {91_m, 0.12_km, Level{23}}}),
        std::invalid_argument);
    // NOLINTNEXTLINE
    EXPECT_THROW(
        (LineSegment{{990_mm, 0.1_dm, Level{0}}, {6_mm, 58.1_um, Level{1}}}),
        std::invalid_argument);
    // NOLINTNEXTLINE
    EXPECT_THROW(
        (LineSegment{{-51.5_cm, -1.68_cm, Level{-10}}, {83_mm, 1.2_mm, Level{-20}}}),
        std::invalid_argument);

    // Start and end point not different
    // NOLINTNEXTLINE
    EXPECT_THROW(
        (LineSegment{{-12.1_m, 93_m, Level{21}}, {-12.1_m, 93_m, Level{21}}}),
        std::invalid_argument);
    // NOLINTNEXTLINE
    EXPECT_THROW(
        (LineSegment{{990_mm, 0.1_dm, Level{0}}, {990_mm, 0.1_dm, Level{0}}}),
        std::invalid_argument);
    // NOLINTNEXTLINE
    EXPECT_THROW(
        (LineSegment{{-51.5_cm, -1.68_cm, Level{-10}}, {-51.5_cm, -1.68_cm, Level{-10}}}),
        std::invalid_argument);
}

TEST(LineSegment, comparisonOperators) // NOLINTLINE
{
    using namespace jps;

    // ==
    EXPECT_TRUE(
        (LineSegment{{10.32423_m, 213_mm, Level{21}}, {21._cm, 902_um, Level{21}}}) ==
        (LineSegment{{10.32423_m, 213_mm, Level{21}}, {21._cm, 902_um, Level{21}}}));
    EXPECT_TRUE(
        (LineSegment{{-989.43854389_cm, 89123.0986_km, Level{1}}, {21.3_m, 9_cm, Level{1}}}) ==
        (LineSegment{{-989.43854389_cm, 89123.0986_km, Level{1}}, {21.3_m, 9_cm, Level{1}}}));
    EXPECT_TRUE(
        (LineSegment{{124_um, 0.123_m, Level{-2}}, {-12_um, 21.01_km, Level{-2}}}) ==
        (LineSegment{{124_um, 0.123_m, Level{-2}}, {-12_um, 21.01_km, Level{-2}}}));
    EXPECT_TRUE(
        (LineSegment{{565._cm, -1239.1_cm, Level{21}}, {94.3_cm, 8.54_cm, Level{21}}}) ==
        (LineSegment{{565._cm, -1239.1_cm, Level{21}}, {94.3_cm, 8.54_cm, Level{21}}}));
    EXPECT_TRUE(
        (LineSegment{{-167.32_m, -272.5_m, Level{-192}}, {-0.111_mm, -11.90_um, Level{-192}}}) ==
        (LineSegment{{-167.32_m, -272.5_m, Level{-192}}, {-0.111_mm, -11.90_um, Level{-192}}}));
    EXPECT_FALSE(
        (LineSegment{{-12.1_m, 93_m, Level{21}}, {-12.1_m, 123_m, Level{21}}}) ==
        (LineSegment{{-167.32_m, -272.5_m, Level{-19214}}, {-0.111_mm, -11.90_um, Level{-19214}}}));
    EXPECT_FALSE(
        (LineSegment{{-34.1_m, 1_m, Level{-21}}, {12.1_m, 23_m, Level{-21}}}) ==
        (LineSegment{{-34.1_m, 1_m, Level{1}}, {12.1_m, 23_m, Level{1}}}));
    EXPECT_FALSE(
        (LineSegment{{-12.1_m, 93_m, Level{21}}, {-12.1_m, 123_m, Level{21}}}) ==
        (LineSegment{{-12.1_m, 94_m, Level{21}}, {-12.1_m, 123_m, Level{21}}}));
    EXPECT_FALSE(
        (LineSegment{{-09.1_m, 7_m, Level{21}}, {-3.1_m, 2_m, Level{21}}}) ==
        (LineSegment{{-6.32_m, -65.5_m, Level{-56}}, {-0.123_mm, -12.2_um, Level{-56}}}));
    EXPECT_FALSE(
        (LineSegment{{0.0_m, 1_m, Level{0}}, {0_m, 1.1_m, Level{0}}}) ==
        (LineSegment{{0_m, 1.1_m, Level{0}}, {0_m, 1_m, Level{0}}}));

    // !=
    EXPECT_TRUE(
        (LineSegment{{-12.1_m, 93_m, Level{21}}, {-12.1_m, 123_m, Level{21}}}) !=
        (LineSegment{{-167.32_m, -272.5_m, Level{-19214}}, {-0.111_mm, -11.90_um, Level{-19214}}}));
    EXPECT_TRUE(
        (LineSegment{{-34.1_m, 1_m, Level{-21}}, {12.1_m, 23_m, Level{-21}}}) !=
        (LineSegment{{-34.1_m, 1_m, Level{1}}, {12.1_m, 23_m, Level{1}}}));
    EXPECT_TRUE(
        (LineSegment{{-12.1_m, 93_m, Level{21}}, {-12.1_m, 123_m, Level{21}}}) !=
        (LineSegment{{-12.1_m, 94_m, Level{21}}, {-12.1_m, 123_m, Level{21}}}));
    EXPECT_TRUE(
        (LineSegment{{-09.1_m, 7_m, Level{21}}, {-3.1_m, 2_m, Level{21}}}) !=
        (LineSegment{{-6.32_m, -65.5_m, Level{-56}}, {-0.123_mm, -12.2_um, Level{-56}}}));
    EXPECT_TRUE(
        (LineSegment{{0.0_m, 1_m, Level{0}}, {0_m, 1.1_m, Level{0}}}) !=
        (LineSegment{{0_m, 1.1_m, Level{0}}, {0_m, 1_m, Level{0}}}));
    EXPECT_FALSE(
        (LineSegment{{10.32423_m, 213_mm, Level{21}}, {21._cm, 902_um, Level{21}}}) !=
        (LineSegment{{10.32423_m, 213_mm, Level{21}}, {21._cm, 902_um, Level{21}}}));
    EXPECT_FALSE(
        (LineSegment{{-989.43854389_cm, 89123.0986_km, Level{1}}, {21.3_m, 9_cm, Level{1}}}) !=
        (LineSegment{{-989.43854389_cm, 89123.0986_km, Level{1}}, {21.3_m, 9_cm, Level{1}}}));
    EXPECT_FALSE(
        (LineSegment{{124_um, 0.123_m, Level{-2}}, {-12_um, 21.01_km, Level{-2}}}) !=
        (LineSegment{{124_um, 0.123_m, Level{-2}}, {-12_um, 21.01_km, Level{-2}}}));
    EXPECT_FALSE(
        (LineSegment{{565._cm, -1239.1_cm, Level{21}}, {94.3_cm, 8.54_cm, Level{21}}}) !=
        (LineSegment{{565._cm, -1239.1_cm, Level{21}}, {94.3_cm, 8.54_cm, Level{21}}}));
    EXPECT_FALSE(
        (LineSegment{{-167.32_m, -272.5_m, Level{-192}}, {-0.111_mm, -11.90_um, Level{-192}}}) !=
        (LineSegment{{-167.32_m, -272.5_m, Level{-192}}, {-0.111_mm, -11.90_um, Level{-192}}}));
}

TEST(LineSegment, rotate) // NOLINTLINE
{
    using namespace jps;
    std::vector<LineSegment> line_segments{
        {{10.32423_m, 213_mm, Level{21}}, {21._cm, 902_um, Level{21}}},
        {{-989.43854389_cm, 89123.0986_km, Level{1}}, {21.3_m, 9_cm, Level{1}}},
        {{124_um, 0.123_m, Level{-2}}, {-12_um, 21.01_km, Level{-2}}},
        {{565._cm, -1239.1_cm, Level{21}}, {94.3_cm, 8.54_cm, Level{21}}},
        {{-167.32_m, -272.5_m, Level{-19214}}, {-0.111_mm, -11.90_um, Level{-19214}}}};

    for(auto line_segment : line_segments) {
        LineSegment rotated = line_segment;
        rotated.rotate();

        EXPECT_TRUE(rotated.getStart() == line_segment.getEnd());
        EXPECT_TRUE(rotated.getEnd() == line_segment.getStart());
    }
}