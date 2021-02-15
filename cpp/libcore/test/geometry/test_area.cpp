#include "geometry/area.hpp"

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <random>

// NOLINTNEXTLINE
TEST(Area, ConstructorFromCoordinate)
{
    using namespace jps;
    using namespace details;

    // Successful
    std::vector<Coordinate> start_end_equal{
        {-10_cm, 0_cm, Level{1}},
        {-20_m, 1_m, Level{1}},
        {-20_m, 4_m, Level{1}},
        {-15_m, 1_m, Level{1}},
        {-10_cm, 0_cm, Level{1}},
    };
    std::vector<Coordinate> start_end_not_equal{start_end_equal};
    start_end_not_equal.pop_back();

    Area area_start_end_equal{start_end_equal};
    EXPECT_THAT(area_start_end_equal.getPolygon(), ::testing::ContainerEq(start_end_not_equal));

    Area area_start_end_not_equal{start_end_not_equal};
    EXPECT_THAT(area_start_end_not_equal.getPolygon(), ::testing::ContainerEq(start_end_not_equal));

    // Failing
    std::vector<Coordinate> empty;
    EXPECT_THROW(Area{empty}, std::runtime_error); // NOLINTLINE

    std::vector<Coordinate> two_elements{
        {10_m, 10_m, Level{1}},
        {10_m, 5_m, Level{1}},
    };
    EXPECT_THROW(Area{two_elements}, std::runtime_error); // NOLINTLINE

    std::vector<Coordinate> different_lvl{
        {10_m, 10_m, Level{1}},
        {10_m, 5_m, Level{1}},
        {5_m, 1_m, Level{3}},
        {5_m, 10_m, Level{1}},
    };
    EXPECT_THROW(Area{different_lvl}, std::runtime_error); // NOLINTLINE
}

// NOLINTNEXTLINE
TEST(Area, ConstructorFromLineSegments)
{
    using namespace jps;
    using namespace details;

    // Successful
    std::vector<Coordinate> coordinates{
        {-4.1_cm, 3.7_cm, Level{1}},
        {3.1_cm, 4.9_cm, Level{1}},
        {7.5_cm, 2.3_cm, Level{1}},
        {9.2_cm, -3.1_cm, Level{1}},
        {4.1_cm, -5.9_cm, Level{1}},
        {1_cm, -1.5_cm, Level{1}},
        {-2_cm, -4.7_cm, Level{1}},
        {-6.3_cm, -2.1_cm, Level{1}}};

    std::vector<LineSegment> sorted;
    for(auto coordinate_itr = std::begin(coordinates); coordinate_itr < std::end(coordinates) - 1;
        ++coordinate_itr) {
        sorted.emplace_back(LineSegment{*coordinate_itr, *std::next(coordinate_itr)});
    }
    sorted.emplace_back(LineSegment{coordinates.back(), coordinates.front()});

    Area area_sorted{sorted};
    EXPECT_THAT(area_sorted.getPolygon(), ::testing::UnorderedElementsAreArray(coordinates));

    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<LineSegment> shuffled{sorted};
    std::shuffle(std::begin(shuffled), std::end(shuffled), g);
    Area area_shuffled{sorted};
    EXPECT_THAT(area_shuffled.getPolygon(), ::testing::UnorderedElementsAreArray(coordinates));

    // Failing
    std::vector<LineSegment> empty;
    EXPECT_THROW(Area{empty}, std::runtime_error); // NOLINTLINE

    std::vector<LineSegment> two_elements{
        {{10_m, 10_m, Level{1}}, {15_m, 10_m, Level{1}}},
        {{15_m, 10_m, Level{1}}, {10_m, 10_m, Level{1}}},
    };
    EXPECT_THROW(Area{two_elements}, std::runtime_error); // NOLINTLINE

    std::vector<LineSegment> different_lvl{
        {{10_m, 10_m, Level{1}}, {15_m, 10_m, Level{1}}},
        {{15_m, 10_m, Level{1}}, {20_m, 10_m, Level{1}}},
        {{20_m, 10_m, Level{2}}, {10_m, 10_m, Level{2}}},
    };
    EXPECT_THROW(Area{different_lvl}, std::runtime_error); // NOLINTLINE

    std::vector<LineSegment> not_sortable_lines_not_connected{
        {{10_m, 10_m, Level{1}}, {15_m, 10_m, Level{1}}},
        {{15_m, 10_m, Level{1}}, {20_m, 10_m, Level{1}}},
        {{20_m, 10_m, Level{1}}, {30_m, 10_m, Level{1}}},
        {{40_m, 10_m, Level{1}}, {10_m, 10_m, Level{1}}},
    };
    EXPECT_THROW(Area{not_sortable_lines_not_connected}, std::runtime_error); // NOLINTLINE

    std::vector<LineSegment> not_closed{
        {{-1_m, 1_m, Level{-1}}, {1_m, 1_m, Level{-1}}},
        {{1_m, 1_m, Level{-1}}, {1_m, -1_m, Level{-1}}},
        {{1_m, -1_m, Level{-1}}, {-1_m, -1_m, Level{-1}}},
    };
    EXPECT_THROW(Area{not_closed}, std::runtime_error); // NOLINTLINE
}

TEST(Area, comparisonOperators) // NOLINTLINE
{
    using namespace jps;
    using namespace details;

    // ==
    EXPECT_TRUE(
        (Area{std::vector<LineSegment>{
            LineSegment{{-4.1_cm, 3.7_cm, Level{1}}, {3.1_cm, 4.9_cm, Level{1}}},
            LineSegment{{3.1_cm, 4.9_cm, Level{1}}, {7.5_cm, 2.3_cm, Level{1}}},
            LineSegment{{7.5_cm, 2.3_cm, Level{1}}, {9.2_cm, -3.1_cm, Level{1}}},
            LineSegment{{9.2_cm, -3.1_cm, Level{1}}, {4.1_cm, -5.9_cm, Level{1}}},
            LineSegment{{4.1_cm, -5.9_cm, Level{1}}, {1_cm, -1.5_cm, Level{1}}},
            LineSegment{{1_cm, -1.5_cm, Level{1}}, {-2_cm, -4.7_cm, Level{1}}},
            LineSegment{{-2_cm, -4.7_cm, Level{1}}, {-6.3_cm, -2.1_cm, Level{1}}},
            LineSegment{{-6.3_cm, -2.1_cm, Level{1}}, {-4.1_cm, 3.7_cm, Level{1}}}}}) ==
        (Area{std::vector<Coordinate>{
            {-4.1_cm, 3.7_cm, Level{1}},
            {3.1_cm, 4.9_cm, Level{1}},
            {7.5_cm, 2.3_cm, Level{1}},
            {9.2_cm, -3.1_cm, Level{1}},
            {4.1_cm, -5.9_cm, Level{1}},
            {1_cm, -1.5_cm, Level{1}},
            {-2_cm, -4.7_cm, Level{1}},
            {-6.3_cm, -2.1_cm, Level{1}}}}));
    EXPECT_TRUE(
        (Area{std::vector<LineSegment>{
            LineSegment{{4.1_cm, -5.9_cm, Level{1}}, {1_cm, -1.5_cm, Level{1}}},
            LineSegment{{-4.1_cm, 3.7_cm, Level{1}}, {3.1_cm, 4.9_cm, Level{1}}},
            LineSegment{{3.1_cm, 4.9_cm, Level{1}}, {7.5_cm, 2.3_cm, Level{1}}},
            LineSegment{{1_cm, -1.5_cm, Level{1}}, {-2_cm, -4.7_cm, Level{1}}},
            LineSegment{{7.5_cm, 2.3_cm, Level{1}}, {9.2_cm, -3.1_cm, Level{1}}},
            LineSegment{{-2_cm, -4.7_cm, Level{1}}, {-6.3_cm, -2.1_cm, Level{1}}},
            LineSegment{{9.2_cm, -3.1_cm, Level{1}}, {4.1_cm, -5.9_cm, Level{1}}},
            LineSegment{{-6.3_cm, -2.1_cm, Level{1}}, {-4.1_cm, 3.7_cm, Level{1}}}}}) ==
        (Area{std::vector<Coordinate>{
            {-4.1_cm, 3.7_cm, Level{1}},
            {3.1_cm, 4.9_cm, Level{1}},
            {7.5_cm, 2.3_cm, Level{1}},
            {9.2_cm, -3.1_cm, Level{1}},
            {4.1_cm, -5.9_cm, Level{1}},
            {1_cm, -1.5_cm, Level{1}},
            {-2_cm, -4.7_cm, Level{1}},
            {-6.3_cm, -2.1_cm, Level{1}}}}));
    EXPECT_FALSE(
        (Area{std::vector<Coordinate>{
            {-4.1_cm, 3.7_cm, Level{1}},
            {3.1_cm, 4.9_cm, Level{1}},
            {7.5_cm, 2.3_cm, Level{1}},
            {9.2_cm, -3.1_cm, Level{1}},
            {4.1_cm, -5.9_cm, Level{1}},
            {1_cm, -1.5_cm, Level{1}},
            {-2_cm, -4.7_cm, Level{1}},
            {-6.3_cm, -2.1_cm, Level{1}}}}) == (Area{std::vector<Coordinate>{
                                                   {-4.1_cm, 3.7_cm, Level{1}},
                                                   {3.1_cm, 4.9_cm, Level{1}},
                                                   {9.2_cm, -3.1_cm, Level{1}},
                                                   {4.1_cm, -5.9_cm, Level{1}},
                                                   {-2_cm, -4.7_cm, Level{1}},
                                                   {-6.3_cm, -2.1_cm, Level{1}}}}));
    EXPECT_FALSE(
        (Area{std::vector<Coordinate>{
            {-4.1_cm, 3.7_cm, Level{1}},
            {3.1_cm, 4.9_cm, Level{1}},
            {7.5_cm, 2.3_cm, Level{1}},
            {1_cm, -1.5_cm, Level{1}},
            {-2_cm, -4.7_cm, Level{1}},
            {-6.3_cm, -2.1_cm, Level{1}}}}) == (Area{std::vector<Coordinate>{
                                                   {-4.1_cm, 3.7_cm, Level{1}},
                                                   {3.1_cm, 4.9_cm, Level{1}},
                                                   {9.2_cm, -3.1_cm, Level{1}},
                                                   {-2_cm, -4.7_cm, Level{1}},
                                                   {-6.3_cm, -2.1_cm, Level{1}}}}));


    EXPECT_TRUE(
        (Area{std::vector<Coordinate>{
            {-4.1_cm, 3.7_cm, Level{1}},
            {3.1_cm, 4.9_cm, Level{1}},
            {7.5_cm, 2.3_cm, Level{1}},
            {9.2_cm, -3.1_cm, Level{1}},
            {4.1_cm, -5.9_cm, Level{1}},
            {1_cm, -1.5_cm, Level{1}},
            {-2_cm, -4.7_cm, Level{1}},
            {-6.3_cm, -2.1_cm, Level{1}}}}) != (Area{std::vector<Coordinate>{
                                                   {-4.1_cm, 3.7_cm, Level{1}},
                                                   {3.1_cm, 4.9_cm, Level{1}},
                                                   {9.2_cm, -3.1_cm, Level{1}},
                                                   {4.1_cm, -5.9_cm, Level{1}},
                                                   {-2_cm, -4.7_cm, Level{1}},
                                                   {-6.3_cm, -2.1_cm, Level{1}}}}));
    EXPECT_TRUE(
        (Area{std::vector<Coordinate>{
            {-4.1_cm, 3.7_cm, Level{1}},
            {3.1_cm, 4.9_cm, Level{1}},
            {7.5_cm, 2.3_cm, Level{1}},
            {1_cm, -1.5_cm, Level{1}},
            {-2_cm, -4.7_cm, Level{1}},
            {-6.3_cm, -2.1_cm, Level{1}}}}) != (Area{std::vector<Coordinate>{
                                                   {-4.1_cm, 3.7_cm, Level{1}},
                                                   {3.1_cm, 4.9_cm, Level{1}},
                                                   {9.2_cm, -3.1_cm, Level{1}},
                                                   {-2_cm, -4.7_cm, Level{1}},
                                                   {-6.3_cm, -2.1_cm, Level{1}}}}));
    EXPECT_FALSE(
        (Area{std::vector<LineSegment>{
            LineSegment{{-4.1_cm, 3.7_cm, Level{1}}, {3.1_cm, 4.9_cm, Level{1}}},
            LineSegment{{3.1_cm, 4.9_cm, Level{1}}, {7.5_cm, 2.3_cm, Level{1}}},
            LineSegment{{7.5_cm, 2.3_cm, Level{1}}, {9.2_cm, -3.1_cm, Level{1}}},
            LineSegment{{9.2_cm, -3.1_cm, Level{1}}, {4.1_cm, -5.9_cm, Level{1}}},
            LineSegment{{4.1_cm, -5.9_cm, Level{1}}, {1_cm, -1.5_cm, Level{1}}},
            LineSegment{{1_cm, -1.5_cm, Level{1}}, {-2_cm, -4.7_cm, Level{1}}},
            LineSegment{{-2_cm, -4.7_cm, Level{1}}, {-6.3_cm, -2.1_cm, Level{1}}},
            LineSegment{{-6.3_cm, -2.1_cm, Level{1}}, {-4.1_cm, 3.7_cm, Level{1}}}}}) !=
        (Area{std::vector<Coordinate>{
            {-4.1_cm, 3.7_cm, Level{1}},
            {3.1_cm, 4.9_cm, Level{1}},
            {7.5_cm, 2.3_cm, Level{1}},
            {9.2_cm, -3.1_cm, Level{1}},
            {4.1_cm, -5.9_cm, Level{1}},
            {1_cm, -1.5_cm, Level{1}},
            {-2_cm, -4.7_cm, Level{1}},
            {-6.3_cm, -2.1_cm, Level{1}}}}));
    EXPECT_FALSE(
        (Area{std::vector<LineSegment>{
            LineSegment{{4.1_cm, -5.9_cm, Level{1}}, {1_cm, -1.5_cm, Level{1}}},
            LineSegment{{-4.1_cm, 3.7_cm, Level{1}}, {3.1_cm, 4.9_cm, Level{1}}},
            LineSegment{{3.1_cm, 4.9_cm, Level{1}}, {7.5_cm, 2.3_cm, Level{1}}},
            LineSegment{{1_cm, -1.5_cm, Level{1}}, {-2_cm, -4.7_cm, Level{1}}},
            LineSegment{{7.5_cm, 2.3_cm, Level{1}}, {9.2_cm, -3.1_cm, Level{1}}},
            LineSegment{{-2_cm, -4.7_cm, Level{1}}, {-6.3_cm, -2.1_cm, Level{1}}},
            LineSegment{{9.2_cm, -3.1_cm, Level{1}}, {4.1_cm, -5.9_cm, Level{1}}},
            LineSegment{{-6.3_cm, -2.1_cm, Level{1}}, {-4.1_cm, 3.7_cm, Level{1}}}}}) !=
        (Area{std::vector<Coordinate>{
            {-4.1_cm, 3.7_cm, Level{1}},
            {3.1_cm, 4.9_cm, Level{1}},
            {7.5_cm, 2.3_cm, Level{1}},
            {9.2_cm, -3.1_cm, Level{1}},
            {4.1_cm, -5.9_cm, Level{1}},
            {1_cm, -1.5_cm, Level{1}},
            {-2_cm, -4.7_cm, Level{1}},
            {-6.3_cm, -2.1_cm, Level{1}}}}));
}