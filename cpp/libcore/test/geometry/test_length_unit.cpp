#include "geometry/length_unit.hpp"

#include <gtest/gtest.h>

TEST(LengthUnit, NonHelperConstruction)
{
    using namespace jps;
    using namespace details;

    // Same unit
    EXPECT_EQ(
        (LengthUnit{LengthUnitParams<LengthUnit::QuantityType, Units::km>{10}}.get<Units::km>()),
        10);
    EXPECT_EQ(
        (LengthUnit{LengthUnitParams<LengthUnit::QuantityType, Units::m>{10}}.get<Units::m>()), 10);
    EXPECT_EQ(
        (LengthUnit{LengthUnitParams<LengthUnit::QuantityType, Units::dm>{10}}.get<Units::dm>()),
        10);
    EXPECT_EQ(
        (LengthUnit{LengthUnitParams<LengthUnit::QuantityType, Units::cm>{10}}.get<Units::cm>()),
        10);
    EXPECT_EQ(
        (LengthUnit{LengthUnitParams<LengthUnit::QuantityType, Units::mm>{10}}.get<Units::mm>()),
        10);
    EXPECT_EQ(
        (LengthUnit{LengthUnitParams<LengthUnit::QuantityType, Units::mum>{10}}.get<Units::mum>()),
        10);

    // Check if scaling is used in constructor
    EXPECT_EQ(
        (LengthUnit{LengthUnitParams<LengthUnit::QuantityType, Units::km>{1}}
             .get<LengthUnit::RESOLUTION>()),
        1000000000);
    EXPECT_EQ(
        (LengthUnit{LengthUnitParams<LengthUnit::QuantityType, Units::m>{1}}
             .get<LengthUnit::RESOLUTION>()),
        1000000);
    EXPECT_EQ(
        (LengthUnit{LengthUnitParams<LengthUnit::QuantityType, Units::dm>{1}}
             .get<LengthUnit::RESOLUTION>()),
        100000);
    EXPECT_EQ(
        (LengthUnit{LengthUnitParams<LengthUnit::QuantityType, Units::cm>{1}}
             .get<LengthUnit::RESOLUTION>()),
        10000);
    EXPECT_EQ(
        (LengthUnit{LengthUnitParams<LengthUnit::QuantityType, Units::mm>{1}}
             .get<LengthUnit::RESOLUTION>()),
        1000);

    // Check if scaling is used in get method
    EXPECT_EQ(
        (LengthUnit{LengthUnitParams<LengthUnit::QuantityType, LengthUnit::RESOLUTION>{1000000000}}
             .get<Units::km>()),
        1);
    EXPECT_EQ(
        (LengthUnit{LengthUnitParams<LengthUnit::QuantityType, LengthUnit::RESOLUTION>{1000000}}
             .get<Units::m>()),
        1);
    EXPECT_EQ(
        (LengthUnit{LengthUnitParams<LengthUnit::QuantityType, LengthUnit::RESOLUTION>{100000}}
             .get<Units::dm>()),
        1);
    EXPECT_EQ(
        (LengthUnit{LengthUnitParams<LengthUnit::QuantityType, LengthUnit::RESOLUTION>{10000}}
             .get<Units::cm>()),
        1);
    EXPECT_EQ(
        (LengthUnit{LengthUnitParams<LengthUnit::QuantityType, LengthUnit::RESOLUTION>{1000}}
             .get<Units::mm>()),
        1);
}

TEST(LengthUnit, scaleQuantity)
{
    using namespace jps;
    using namespace details;

    // From km
    EXPECT_EQ((scaleQuantity<Units::km, Units::mum>(1)), 1000000000);
    EXPECT_EQ((scaleQuantity<Units::km, Units::mm>(1)), 1000000);
    EXPECT_EQ((scaleQuantity<Units::km, Units::cm>(1)), 100000);
    EXPECT_EQ((scaleQuantity<Units::km, Units::dm>(1)), 10000);
    EXPECT_EQ((scaleQuantity<Units::km, Units::m>(1)), 1000);

    // From m
    EXPECT_EQ((scaleQuantity<Units::m, Units::km>(1200)), 1);
    EXPECT_EQ((scaleQuantity<Units::m, Units::dm>(2)), 20);
    EXPECT_EQ((scaleQuantity<Units::m, Units::cm>(2)), 200);
    EXPECT_EQ((scaleQuantity<Units::m, Units::mm>(2)), 2000);
    EXPECT_EQ((scaleQuantity<Units::m, Units::mum>(2)), 2000000);

    // From dm
    EXPECT_EQ((scaleQuantity<Units::dm, Units::km>(20000)), 2);
    EXPECT_EQ((scaleQuantity<Units::dm, Units::m>(19)), 1);
    EXPECT_EQ((scaleQuantity<Units::dm, Units::cm>(1)), 10);
    EXPECT_EQ((scaleQuantity<Units::dm, Units::mm>(1)), 100);
    EXPECT_EQ((scaleQuantity<Units::dm, Units::mum>(1)), 100000);

    // From cm
    EXPECT_EQ((scaleQuantity<Units::cm, Units::km>(120000)), 1);
    EXPECT_EQ((scaleQuantity<Units::cm, Units::m>(100)), 1);
    EXPECT_EQ((scaleQuantity<Units::cm, Units::dm>(12)), 1);
    EXPECT_EQ((scaleQuantity<Units::cm, Units::mm>(1)), 10);
    EXPECT_EQ((scaleQuantity<Units::cm, Units::mum>(2)), 20000);

    // From mm
    EXPECT_EQ((scaleQuantity<Units::mm, Units::km>(5000000)), 5);
    EXPECT_EQ((scaleQuantity<Units::mm, Units::m>(1200)), 1);
    EXPECT_EQ((scaleQuantity<Units::mm, Units::dm>(540)), 5);
    EXPECT_EQ((scaleQuantity<Units::mm, Units::cm>(78)), 7);
    EXPECT_EQ((scaleQuantity<Units::mm, Units::mum>(5)), 5000);

    // From mum
    EXPECT_EQ((scaleQuantity<Units::mum, Units::km>(1234763874)), 1);
    EXPECT_EQ((scaleQuantity<Units::mum, Units::m>(1846574)), 1);
    EXPECT_EQ((scaleQuantity<Units::mum, Units::dm>(192837)), 1);
    EXPECT_EQ((scaleQuantity<Units::mum, Units::cm>(13823)), 1);
    EXPECT_EQ((scaleQuantity<Units::mum, Units::mm>(1234)), 1);
}
