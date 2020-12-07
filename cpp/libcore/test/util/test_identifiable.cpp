#include "util/identifiable.hpp"

#include <gtest/gtest.h>
#include <memory>


TEST(Identifiable, EmptyConstructed)
{
    class Identified1 : public jps::Identifiable<Identified1>
    {
    };

    Identified1 obj1;
    // UID should start with 0
    EXPECT_EQ(obj1.getID(), 0);

    // new object should get next UID
    Identified1 obj2;
    EXPECT_EQ(obj1.getID(), 0);
    EXPECT_EQ(obj2.getID(), 1);

    // dynamic allocated gets new UID
    auto obj_ptr = std::make_unique<Identified1>();
    EXPECT_EQ(obj1.getID(), 0);
    EXPECT_EQ(obj2.getID(), 1);
    EXPECT_EQ(obj_ptr->getID(), 2);

    // gaps of UIDs should not be filled
    obj_ptr = nullptr;
    Identified1 obj3;
    EXPECT_EQ(obj1.getID(), 0);
    EXPECT_EQ(obj2.getID(), 1);
    EXPECT_EQ(obj3.getID(), 3);
}

TEST(Identifiable, Move)
{
    // Moving keeps the UID

    class Identified1 : public jps::Identifiable<Identified1>
    {
    };


    Identified1 obj1;
    EXPECT_EQ(obj1.getID(), 0);

    Identified1 obj2{std::move(obj1)};
    EXPECT_EQ(obj2.getID(), 0);
}
