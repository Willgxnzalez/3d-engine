#include <gtest/gtest.h>
#include "ecs/SparseSet.h"

using namespace engine;

struct TestTransform {
    int  x;
    bool active;
};

TEST(SparseSetTest, AddAndContains)
{
    SparseSet<TestTransform> set;
    set.add(5, {10, true});
    EXPECT_TRUE(set.contains(5));
    EXPECT_FALSE(set.contains(3));
}

TEST(SparseSetTest, GetComponent)
{
    SparseSet<TestTransform> set;
    set.add(5, {10, true});
    EXPECT_EQ(set.get(5).x, 10);
    EXPECT_EQ(set.get(5).active, true);
}

TEST(SparseSetTest, RemoveInvalidates)
{
    SparseSet<TestTransform> set;
    set.add(5, {10, true});
    set.remove(5);
    EXPECT_FALSE(set.contains(5));
}

TEST(SparseSetTest, SwapAndPopPreservesOthers)
{
    SparseSet<TestTransform> set;
    set.add(2, {1, true});
    set.add(5, {2, false});
    set.add(8, {3, true});

    set.remove(5);

    EXPECT_TRUE(set.contains(2));
    EXPECT_FALSE(set.contains(5));
    EXPECT_TRUE(set.contains(8));

    EXPECT_EQ(set.get(2).x, 1);
    EXPECT_EQ(set.get(8).x, 3);
}

TEST(SparseSetTest, DenseArrayRemainsContiguous)
{
    SparseSet<TestTransform> set;
    set.add(2, {1, true});
    set.add(5, {2, false});
    set.add(6, {3, false});
    set.add(8, {4, true});

    set.remove(5);
    set.remove(6);

    EXPECT_EQ(set.size(), 2);
    EXPECT_EQ(set.data().size(), 2);
    EXPECT_EQ(set.entities().size(), 2);
}

TEST(SparseSetTest, RemoveLastElement)
{
    SparseSet<TestTransform> set;
    set.add(3, {5, false});
    set.remove(3);
    EXPECT_EQ(set.size(), 0);
    EXPECT_FALSE(set.contains(3));
}

TEST(SparseSetTest, AddAfterRemove)
{
    SparseSet<TestTransform> set;
    set.add(5, {1, true});
    set.remove(5);
    set.add(5, {99, false});
    EXPECT_TRUE(set.contains(5));
    EXPECT_EQ(set.get(5).x, 99);
}

TEST(SparseSetTest, Clear)
{
    SparseSet<TestTransform> set;
    set.add(1, {1, true});
    set.add(2, {2, false});
    set.clear();
    EXPECT_EQ(set.size(), 0);
    EXPECT_FALSE(set.contains(1));
    EXPECT_FALSE(set.contains(2));
}