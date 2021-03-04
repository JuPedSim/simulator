#include "geometry/helper/polygon_helper.hpp"
#include "geometry/line_segment.hpp"

#include <gtest/gtest.h>

auto checkConnectivity(const std::vector<jps::LineSegment> & p_line_segments) -> void
{
    if(p_line_segments.size() > 1) {
        for(auto wall_itr = std::begin(p_line_segments); wall_itr != std::end(p_line_segments) - 1;
            ++wall_itr) {
            EXPECT_EQ(wall_itr->getEnd(), std::next(wall_itr)->getStart());
        }
    }
}

TEST(GeometryHelper, sortLineSegments)
{
    using namespace jps;
    using namespace geometry;

    // Successful
    {
        std::vector<LineSegment> empty;
        EXPECT_NO_THROW(sortLineSegments(empty));
        EXPECT_TRUE(empty.empty());
        checkConnectivity(empty);

        std::vector<LineSegment> one_element{
            {{990_mm, 0.1_dm, Level{1}}, {1_mm, 0.1_km, Level{1}}}};
        EXPECT_NO_THROW(sortLineSegments(one_element));
        EXPECT_EQ(one_element.size(), 1);
        checkConnectivity(one_element);

        std::vector<LineSegment> pre_sorted{
            {{12_cm, 4_cm, Level{-1}}, {5.1_cm, -0.1_dm, Level{-1}}},
            {{5.1_cm, -0.1_dm, Level{-1}}, {-0.02_m, -20_mm, Level{-1}}},
            {{-0.02_m, -20_mm, Level{-1}}, {-15_cm, 30_mm, Level{-1}}},
            {{-15_cm, 30_mm, Level{-1}}, {12_cm, 4_cm, Level{-1}}}};
        EXPECT_NO_THROW(sortLineSegments(pre_sorted));
        checkConnectivity(pre_sorted);

        std::vector<LineSegment> without_rotation{
            {{3.1_m, 57_dm, Level{1}}, {1.1_m, 3_m, Level{1}}},
            {{0.1_m, 0.5_m, Level{1}}, {3.1_m, 57_dm, Level{1}}},
            {{-10.8_cm, 31_dm, Level{1}}, {-5.1_m, -2.4_m, Level{1}}},
            {{1.1_m, 3_m, Level{1}}, {-10.8_cm, 31_dm, Level{1}}},
            {{-5.1_m, -2.4_m, Level{1}}, {0.1_m, 0.5_m, Level{1}}},
        };
        EXPECT_NO_THROW(sortLineSegments(without_rotation));
        checkConnectivity(without_rotation);

        std::vector<LineSegment> with_rotation{
            {{3.1_m, 57_dm, Level{1}}, {1.1_m, 3_m, Level{1}}},
            {{0.1_m, 0.5_m, Level{1}}, {3.1_m, 57_dm, Level{1}}},
            {{-5.1_m, -2.4_m, Level{1}}, {-10.8_cm, 31_dm, Level{1}}},
            {{1.1_m, 3_m, Level{1}}, {-10.8_cm, 31_dm, Level{1}}},
            {{0.1_m, 0.5_m, Level{1}}, {-5.1_m, -2.4_m, Level{1}}},
        };
        EXPECT_NO_THROW(sortLineSegments(with_rotation));
        checkConnectivity(with_rotation);
    }

    // Not successful
    {
        std::vector<LineSegment> no_connection{
            {{3.1_m, 57_dm, Level{1}}, {1.1_m, 3_m, Level{1}}},
            {{0.1_m, 0.5_m, Level{1}}, {3.1_m, 57_dm, Level{1}}},
            {{1.1_m, 3_m, Level{1}}, {-10.8_cm, 31_dm, Level{1}}},
            {{0.1_m, 0.5_m, Level{1}}, {-5.1_m, -2.4_m, Level{1}}},
        };
        EXPECT_THROW(sortLineSegments(no_connection), std::runtime_error);

        std::vector<LineSegment> duplicate_line_segment{
            {{3.1_m, 57_dm, Level{1}}, {1.1_m, 3_m, Level{1}}},
            {{0.1_m, 0.5_m, Level{1}}, {3.1_m, 57_dm, Level{1}}},
            {{-5.1_m, -2.4_m, Level{1}}, {-10.8_cm, 31_dm, Level{1}}},
            {{1.1_m, 3_m, Level{1}}, {-10.8_cm, 31_dm, Level{1}}},
            {{0.1_m, 0.5_m, Level{1}}, {-5.1_m, -2.4_m, Level{1}}},
            {{0.1_m, 0.5_m, Level{1}}, {-5.1_m, -2.4_m, Level{1}}},
        };
        EXPECT_THROW(sortLineSegments(duplicate_line_segment), std::runtime_error);

        std::vector<LineSegment> different_levels{
            {{3.1_m, 57_dm, Level{1}}, {1.1_m, 3_m, Level{1}}},
            {{0.1_m, 0.5_m, Level{1}}, {3.1_m, 57_dm, Level{1}}},
            {{-5.1_m, -2.4_m, Level{1}}, {-10.8_cm, 31_dm, Level{1}}},
            {{1.1_m, 3_m, Level{1}}, {-10.8_cm, 31_dm, Level{1}}},
            {{0.1_m, 0.5_m, Level{2}}, {-5.1_m, -2.4_m, Level{2}}},
        };
        EXPECT_THROW(sortLineSegments(different_levels), std::runtime_error); // NOLINTLINE
    }
}

TEST(GeometryHelper, getPolygonCoordinates) // NOLINTLINE
{
    using namespace jps;
    using namespace geometry;

    // Successful
    {
        std::vector<Coordinate> coordinates{
            {-3.8_m, 2.5_m, Level{1}},
            {-0.9_m, 1.2_m, Level{1}},
            {1.1_m, 5.2_m, Level{1}},
            {3.7_m, 3.9_m, Level{1}},
            {5.3_m, 1.1_m, Level{1}},
            {2.2_m, -.7_m, Level{1}},
            {2.8_m, -3.6_m, Level{1}},
            {1.9_m, -3.6_m, Level{1}},
            {-4.2_m, 0.8_m, Level{1}},
        };

        std::vector<LineSegment> without_rotation;
        std::vector<LineSegment> with_rotation;
        for(size_t i = 0; i < coordinates.size(); ++i) {
            without_rotation.emplace_back(
                LineSegment{coordinates.at(i), coordinates.at((i + 1) % coordinates.size())});
            with_rotation.emplace_back(
                LineSegment{coordinates.at(i), coordinates.at((i + 1) % coordinates.size())});
            // first element needs to be not rotated, otherwise get sorted reversely
            if((i % 3) == 1) {
                with_rotation.back().rotate();
            }
        }

        auto coordinates_without_rotation = getPolygonCoordinates(without_rotation);
        EXPECT_TRUE(checkPolygonEquality(coordinates, coordinates_without_rotation));

        auto coordinates_with_rotation = getPolygonCoordinates(with_rotation);
        EXPECT_TRUE(checkPolygonEquality(coordinates, coordinates_with_rotation));
    }

    // Not successful
    {
        std::vector<LineSegment> empty;
        EXPECT_THROW(getPolygonCoordinates(empty), std::runtime_error); // NOLINTLINE

        std::vector<LineSegment> less_than_three_elements{
            {{0.1_m, 0.5_m, Level{1}}, {3.1_m, 57_dm, Level{1}}},
            {{-5.1_m, -2.4_m, Level{1}}, {-10.8_cm, 31_dm, Level{1}}},
        };
        // NOLINTNEXTLINE
        EXPECT_THROW(getPolygonCoordinates(less_than_three_elements), std::runtime_error);

        std::vector<LineSegment> different_levels{
            {{0.1_m, 0.5_m, Level{1}}, {3.1_m, 57_dm, Level{1}}},
            {{-5.1_m, -2.4_m, Level{1}}, {-10.8_cm, 31_dm, Level{1}}},
            {{1.1_m, 3_m, Level{1}}, {-10.8_cm, 31_dm, Level{1}}},
            {{0.1_m, 0.5_m, Level{2}}, {-5.1_m, -2.4_m, Level{2}}},
        };
        EXPECT_THROW(getPolygonCoordinates(different_levels), std::runtime_error); // NOLINTLINE

        std::vector<LineSegment> not_sortable{
            {{3.1_m, 57_dm, Level{1}}, {1.1_m, 3_m, Level{1}}},
            {{0.1_m, 0.5_m, Level{1}}, {3.1_m, 57_dm, Level{1}}},
            {{1.1_m, 3_m, Level{1}}, {-10.8_cm, 31_dm, Level{1}}},
            {{0.1_m, 0.5_m, Level{1}}, {-5.1_m, -2.4_m, Level{1}}},
        };
        EXPECT_THROW(getPolygonCoordinates(not_sortable), std::runtime_error); // NOLINTLINE

        std::vector<LineSegment> not_closed{
            {{3.1_m, 57_dm, Level{1}}, {1.1_m, 3_m, Level{1}}},
            {{-5.1_m, -2.4_m, Level{1}}, {-10.8_cm, 31_dm, Level{1}}},
            {{1.1_m, 3_m, Level{1}}, {-10.8_cm, 31_dm, Level{1}}},
            {{0.1_m, 0.5_m, Level{1}}, {-5.1_m, -2.4_m, Level{1}}},
        };
        EXPECT_THROW(getPolygonCoordinates(not_closed), std::runtime_error); // NOLINTLINE
    }
}

TEST(GeometryHelper, checkPolygonEquality) // NOLINTLINE
{
    using namespace jps;
    using namespace geometry;

    std::vector<Coordinate> reference_coordinates{
        {-3.8_m, 2.5_m, Level{1}},
        {-0.9_m, 1.2_m, Level{1}},
        {1.1_m, 5.2_m, Level{1}},
        {3.7_m, 3.9_m, Level{1}},
        {5.3_m, 1.1_m, Level{1}},
        {2.2_m, -.7_m, Level{1}},
        {2.8_m, -3.6_m, Level{1}},
        {1.9_m, -3.6_m, Level{1}},
        {-4.2_m, 0.8_m, Level{1}},
    };

    // same values
    std::vector<Coordinate> equal{reference_coordinates}; // NOLINTLINE
    EXPECT_TRUE(checkPolygonEquality(equal, reference_coordinates));
    std::vector<Coordinate> equal_reversed{std::rbegin(equal), std::rend(equal)};
    EXPECT_TRUE(checkPolygonEquality(equal_reversed, reference_coordinates));

    // rotate vector
    std::rotate(std::begin(equal), std::begin(equal) + 5, std::end(equal));
    EXPECT_TRUE(checkPolygonEquality(equal, reference_coordinates));
    std::reverse_copy(std::begin(equal), std::end(equal), std::begin(equal_reversed));
    EXPECT_TRUE(checkPolygonEquality(equal_reversed, reference_coordinates));

    std::rotate(std::begin(equal), std::begin(equal) + 5, std::end(equal));
    EXPECT_TRUE(checkPolygonEquality(equal, reference_coordinates));
    std::reverse_copy(std::begin(equal), std::end(equal), std::begin(equal_reversed));
    EXPECT_TRUE(checkPolygonEquality(equal_reversed, reference_coordinates));

    std::vector<Coordinate> empty;
    EXPECT_FALSE(checkPolygonEquality(empty, reference_coordinates));

    std::vector<Coordinate> subset{reference_coordinates};
    subset.pop_back();
    EXPECT_FALSE(checkPolygonEquality(subset, reference_coordinates));
    std::vector<Coordinate> subset_reversed{std::rbegin(subset), std::rend(subset)};
    EXPECT_FALSE(checkPolygonEquality(subset_reversed, reference_coordinates));

    std::vector<Coordinate> switch_two_elements{reference_coordinates};
    std::iter_swap(std::begin(switch_two_elements), std::begin(switch_two_elements) + 3);
    EXPECT_FALSE(checkPolygonEquality(switch_two_elements, reference_coordinates));
    std::vector<Coordinate> switch_two_reversed{
        std::rbegin(switch_two_elements), std::rend(switch_two_elements)};
    EXPECT_FALSE(checkPolygonEquality(switch_two_reversed, reference_coordinates));
}
