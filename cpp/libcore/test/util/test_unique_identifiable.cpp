#include "util/unique_identifiable.hpp"

#include <gtest/gtest.h>
#include <memory>


TEST(UniqueIdentifiable, EmptyConstructed)
{
    class Identified1 : public jps::UniqueIdentifiable<Identified1>
    {
    };

    Identified1 obj1;
    // UID should start with 0
    EXPECT_EQ(obj1.getUID(), 0);

    // new object should get next UID
    Identified1 obj2;
    EXPECT_EQ(obj1.getUID(), 0);
    EXPECT_EQ(obj2.getUID(), 1);

    // dynamic allocated gets new UID
    auto obj_ptr = std::make_unique<Identified1>();
    EXPECT_EQ(obj1.getUID(), 0);
    EXPECT_EQ(obj2.getUID(), 1);
    EXPECT_EQ(obj_ptr->getUID(), 2);

    // gaps of UIDs should not be filled
    obj_ptr = nullptr;
    Identified1 obj3;
    EXPECT_EQ(obj1.getUID(), 0);
    EXPECT_EQ(obj2.getUID(), 1);
    EXPECT_EQ(obj3.getUID(), 3);
}


TEST(UniqueIdentifiable, Copy)
{
    // Copying increases the UID

    class Identified1 : public jps::UniqueIdentifiable<Identified1>
    {
    };


    Identified1 obj1;
    Identified1 obj2{obj1}; // NOLINT(performance-unnecessary-copy-initialization)

    EXPECT_EQ(obj1.getUID(), 0);
    EXPECT_EQ(obj2.getUID(), 1);

    obj2 = obj1;
    EXPECT_EQ(obj1.getUID(), 0);
    EXPECT_EQ(obj2.getUID(), 2);
}


TEST(UniqueIdentifiable, Move)
{
    // Moving keeps the UID

    class Identified1 : public jps::UniqueIdentifiable<Identified1>
    {
    };


    Identified1 obj1;
    EXPECT_EQ(obj1.getUID(), 0);

    Identified1 obj2{std::move(obj1)};
    EXPECT_EQ(obj2.getUID(), 0);
}
