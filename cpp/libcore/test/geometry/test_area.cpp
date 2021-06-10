#include "geometry/area.hpp"
#include "util/jpsexception.hpp"

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <random>

TEST(Area, ConstructorFromCoordinate)
{
    using namespace jps;
    using namespace details;

    // Successful
    std::vector<Coordinate> start_end_equal{
        {-10_cm, 0_cm},
        {-20_m, 1_m},
        {-20_m, 4_m},
        {-15_m, 1_m},
        {-10_cm, 0_cm},
    };
    std::vector<Coordinate> start_end_not_equal{start_end_equal};
    start_end_not_equal.pop_back();

    Area area_start_end_equal{start_end_equal};
    EXPECT_THAT(area_start_end_equal.getPolygon(), ::testing::ContainerEq(start_end_not_equal));

    Area area_start_end_not_equal{start_end_not_equal};
    EXPECT_THAT(area_start_end_not_equal.getPolygon(), ::testing::ContainerEq(start_end_not_equal));

    // Failing
    std::vector<Coordinate> empty;
    EXPECT_THROW(Area{empty}, JPSGeometryException);

    std::vector<Coordinate> two_elements{
        {10_m, 10_m},
        {10_m, 5_m},
    };
    EXPECT_THROW(Area{two_elements}, JPSGeometryException);
}

TEST(Area, ConstructorFromLineSegments)
{
    using namespace jps;
    using namespace details;

    // Successful
    std::vector<Coordinate> coordinates{
        {-4.1_cm, 3.7_cm},
        {3.1_cm, 4.9_cm},
        {7.5_cm, 2.3_cm},
        {9.2_cm, -3.1_cm},
        {4.1_cm, -5.9_cm},
        {1_cm, -1.5_cm},
        {-2_cm, -4.7_cm},
        {-6.3_cm, -2.1_cm}};

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
    EXPECT_THROW(Area{empty}, JPSGeometryException);

    std::vector<LineSegment> two_elements{
        {{10_m, 10_m}, {15_m, 10_m}},
        {{15_m, 10_m}, {10_m, 10_m}},
    };
    EXPECT_THROW(Area{two_elements}, JPSGeometryException);

    std::vector<LineSegment> not_sortable_lines_not_connected{
        {{10_m, 10_m}, {15_m, 10_m}},
        {{15_m, 10_m}, {20_m, 10_m}},
        {{20_m, 10_m}, {30_m, 10_m}},
        {{40_m, 10_m}, {10_m, 10_m}},
    };
    EXPECT_THROW(Area{not_sortable_lines_not_connected}, JPSGeometryException);

    std::vector<LineSegment> not_closed{
        {{-1_m, 1_m}, {1_m, 1_m}},
        {{1_m, 1_m}, {1_m, -1_m}},
        {{1_m, -1_m}, {-1_m, -1_m}},
    };
    EXPECT_THROW(Area{not_closed}, JPSGeometryException);
}

TEST(Area, comparisonOperators)
{
    using namespace jps;
    using namespace details;

    // ==
    EXPECT_TRUE(
        (Area{std::vector<LineSegment>{
            LineSegment{{-4.1_cm, 3.7_cm}, {3.1_cm, 4.9_cm}},
            LineSegment{{3.1_cm, 4.9_cm}, {7.5_cm, 2.3_cm}},
            LineSegment{{7.5_cm, 2.3_cm}, {9.2_cm, -3.1_cm}},
            LineSegment{{9.2_cm, -3.1_cm}, {4.1_cm, -5.9_cm}},
            LineSegment{{4.1_cm, -5.9_cm}, {1_cm, -1.5_cm}},
            LineSegment{{1_cm, -1.5_cm}, {-2_cm, -4.7_cm}},
            LineSegment{{-2_cm, -4.7_cm}, {-6.3_cm, -2.1_cm}},
            LineSegment{{-6.3_cm, -2.1_cm}, {-4.1_cm, 3.7_cm}}}}) == (Area{std::vector<Coordinate>{
                                                                         {-4.1_cm, 3.7_cm},
                                                                         {3.1_cm, 4.9_cm},
                                                                         {7.5_cm, 2.3_cm},
                                                                         {9.2_cm, -3.1_cm},
                                                                         {4.1_cm, -5.9_cm},
                                                                         {1_cm, -1.5_cm},
                                                                         {-2_cm, -4.7_cm},
                                                                         {-6.3_cm, -2.1_cm}}}));
    EXPECT_TRUE(
        (Area{std::vector<LineSegment>{
            LineSegment{{4.1_cm, -5.9_cm}, {1_cm, -1.5_cm}},
            LineSegment{{-4.1_cm, 3.7_cm}, {3.1_cm, 4.9_cm}},
            LineSegment{{3.1_cm, 4.9_cm}, {7.5_cm, 2.3_cm}},
            LineSegment{{1_cm, -1.5_cm}, {-2_cm, -4.7_cm}},
            LineSegment{{7.5_cm, 2.3_cm}, {9.2_cm, -3.1_cm}},
            LineSegment{{-2_cm, -4.7_cm}, {-6.3_cm, -2.1_cm}},
            LineSegment{{9.2_cm, -3.1_cm}, {4.1_cm, -5.9_cm}},
            LineSegment{{-6.3_cm, -2.1_cm}, {-4.1_cm, 3.7_cm}}}}) == (Area{std::vector<Coordinate>{
                                                                         {-4.1_cm, 3.7_cm},
                                                                         {3.1_cm, 4.9_cm},
                                                                         {7.5_cm, 2.3_cm},
                                                                         {9.2_cm, -3.1_cm},
                                                                         {4.1_cm, -5.9_cm},
                                                                         {1_cm, -1.5_cm},
                                                                         {-2_cm, -4.7_cm},
                                                                         {-6.3_cm, -2.1_cm}}}));
    EXPECT_FALSE(
        (Area{std::vector<Coordinate>{
            {-4.1_cm, 3.7_cm},
            {3.1_cm, 4.9_cm},
            {7.5_cm, 2.3_cm},
            {9.2_cm, -3.1_cm},
            {4.1_cm, -5.9_cm},
            {1_cm, -1.5_cm},
            {-2_cm, -4.7_cm},
            {-6.3_cm, -2.1_cm}}}) == (Area{std::vector<Coordinate>{
                                         {-4.1_cm, 3.7_cm},
                                         {3.1_cm, 4.9_cm},
                                         {9.2_cm, -3.1_cm},
                                         {4.1_cm, -5.9_cm},
                                         {-2_cm, -4.7_cm},
                                         {-6.3_cm, -2.1_cm}}}));
    EXPECT_FALSE(
        (Area{std::vector<Coordinate>{
            {-4.1_cm, 3.7_cm},
            {3.1_cm, 4.9_cm},
            {7.5_cm, 2.3_cm},
            {1_cm, -1.5_cm},
            {-2_cm, -4.7_cm},
            {-6.3_cm, -2.1_cm}}}) == (Area{std::vector<Coordinate>{
                                         {-4.1_cm, 3.7_cm},
                                         {3.1_cm, 4.9_cm},
                                         {9.2_cm, -3.1_cm},
                                         {-2_cm, -4.7_cm},
                                         {-6.3_cm, -2.1_cm}}}));


    // !=
    EXPECT_TRUE(
        (Area{std::vector<Coordinate>{
            {-4.1_cm, 3.7_cm},
            {3.1_cm, 4.9_cm},
            {7.5_cm, 2.3_cm},
            {9.2_cm, -3.1_cm},
            {4.1_cm, -5.9_cm},
            {1_cm, -1.5_cm},
            {-2_cm, -4.7_cm},
            {-6.3_cm, -2.1_cm}}}) != (Area{std::vector<Coordinate>{
                                         {-4.1_cm, 3.7_cm},
                                         {3.1_cm, 4.9_cm},
                                         {9.2_cm, -3.1_cm},
                                         {4.1_cm, -5.9_cm},
                                         {-2_cm, -4.7_cm},
                                         {-6.3_cm, -2.1_cm}}}));
    EXPECT_TRUE(
        (Area{std::vector<Coordinate>{
            {-4.1_cm, 3.7_cm},
            {3.1_cm, 4.9_cm},
            {7.5_cm, 2.3_cm},
            {1_cm, -1.5_cm},
            {-2_cm, -4.7_cm},
            {-6.3_cm, -2.1_cm}}}) != (Area{std::vector<Coordinate>{
                                         {-4.1_cm, 3.7_cm},
                                         {3.1_cm, 4.9_cm},
                                         {9.2_cm, -3.1_cm},
                                         {-2_cm, -4.7_cm},
                                         {-6.3_cm, -2.1_cm}}}));
    EXPECT_FALSE(
        (Area{std::vector<LineSegment>{
            LineSegment{{-4.1_cm, 3.7_cm}, {3.1_cm, 4.9_cm}},
            LineSegment{{3.1_cm, 4.9_cm}, {7.5_cm, 2.3_cm}},
            LineSegment{{7.5_cm, 2.3_cm}, {9.2_cm, -3.1_cm}},
            LineSegment{{9.2_cm, -3.1_cm}, {4.1_cm, -5.9_cm}},
            LineSegment{{4.1_cm, -5.9_cm}, {1_cm, -1.5_cm}},
            LineSegment{{1_cm, -1.5_cm}, {-2_cm, -4.7_cm}},
            LineSegment{{-2_cm, -4.7_cm}, {-6.3_cm, -2.1_cm}},
            LineSegment{{-6.3_cm, -2.1_cm}, {-4.1_cm, 3.7_cm}}}}) != (Area{std::vector<Coordinate>{
                                                                         {-4.1_cm, 3.7_cm},
                                                                         {3.1_cm, 4.9_cm},
                                                                         {7.5_cm, 2.3_cm},
                                                                         {9.2_cm, -3.1_cm},
                                                                         {4.1_cm, -5.9_cm},
                                                                         {1_cm, -1.5_cm},
                                                                         {-2_cm, -4.7_cm},
                                                                         {-6.3_cm, -2.1_cm}}}));
    EXPECT_FALSE(
        (Area{std::vector<LineSegment>{
            LineSegment{{4.1_cm, -5.9_cm}, {1_cm, -1.5_cm}},
            LineSegment{{-4.1_cm, 3.7_cm}, {3.1_cm, 4.9_cm}},
            LineSegment{{3.1_cm, 4.9_cm}, {7.5_cm, 2.3_cm}},
            LineSegment{{1_cm, -1.5_cm}, {-2_cm, -4.7_cm}},
            LineSegment{{7.5_cm, 2.3_cm}, {9.2_cm, -3.1_cm}},
            LineSegment{{-2_cm, -4.7_cm}, {-6.3_cm, -2.1_cm}},
            LineSegment{{9.2_cm, -3.1_cm}, {4.1_cm, -5.9_cm}},
            LineSegment{{-6.3_cm, -2.1_cm}, {-4.1_cm, 3.7_cm}}}}) != (Area{std::vector<Coordinate>{
                                                                         {-4.1_cm, 3.7_cm},
                                                                         {3.1_cm, 4.9_cm},
                                                                         {7.5_cm, 2.3_cm},
                                                                         {9.2_cm, -3.1_cm},
                                                                         {4.1_cm, -5.9_cm},
                                                                         {1_cm, -1.5_cm},
                                                                         {-2_cm, -4.7_cm},
                                                                         {-6.3_cm, -2.1_cm}}}));

    // rotated
    EXPECT_FALSE(
        (Area{std::vector<Coordinate>{
            {-4.1_cm, 3.7_cm},
            {3.1_cm, 4.9_cm},
            {7.5_cm, 2.3_cm},
            {1_cm, -1.5_cm},
            {-2_cm, -4.7_cm},
            {-6.3_cm, -2.1_cm}}}) == (Area{std::vector<Coordinate>{
                                         {3.1_cm, 4.9_cm},
                                         {1_cm, -1.5_cm},
                                         {7.5_cm, 2.3_cm},
                                         {-4.1_cm, 3.7_cm},
                                         {-2_cm, -4.7_cm},
                                         {-6.3_cm, -2.1_cm}}}));

    EXPECT_TRUE(
        (Area{std::vector<Coordinate>{
            {-4.1_cm, 3.7_cm},
            {3.1_cm, 4.9_cm},
            {7.5_cm, 2.3_cm},
            {1_cm, -1.5_cm},
            {-2_cm, -4.7_cm},
            {-6.3_cm, -2.1_cm}}}) == (Area{std::vector<Coordinate>{
                                         {1_cm, -1.5_cm},
                                         {-2_cm, -4.7_cm},
                                         {-6.3_cm, -2.1_cm},
                                         {-4.1_cm, 3.7_cm},
                                         {3.1_cm, 4.9_cm},
                                         {7.5_cm, 2.3_cm}}}));
}
