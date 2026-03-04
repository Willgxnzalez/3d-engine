#include <gtest/gtest.h>
#include "ecs/Registry.h"
#include "ecs/Entity.h"

using namespace engine;

TEST(EntityTest, CreateisValid)
{
    Registry registry;
    Entity e = registry.createEntity();
    EXPECT_TRUE(e.isValid());
    EXPECT_TRUE(e);
}

TEST(EntityTest, destroyInvalidatesHandle)
{
    Registry registry;
    Entity e = registry.createEntity();
    e.destroy();
    EXPECT_FALSE(e.isValid());
}

TEST(EntityTest, StaleHandleAfterdestroy)
{
    Registry registry;
    Entity e1 = registry.createEntity();
    Entity stale = e1;  // copy the handle

    e1.destroy();

    EXPECT_FALSE(stale.isValid());  // stale handle must detect destruction
}

TEST(EntityTest, RecycledSlotDifferentVersion)
{
    Registry registry;
    Entity e1 = registry.createEntity();
    uint32_t oldID = e1.getID();
    e1.destroy();

    Entity e2 = registry.createEntity();  // should reuse e1's slot
    EXPECT_EQ(e2.getID(), oldID);         // same index
    EXPECT_FALSE(e1.isValid());           // but e1 is still dead
    EXPECT_TRUE(e2.isValid());
}

TEST(EntityTest, MultipleEntitiesIndependent)
{
    Registry registry;
    Entity e1 = registry.createEntity();
    Entity e2 = registry.createEntity();
    Entity e3 = registry.createEntity();

    e2.destroy();

    EXPECT_TRUE(e1.isValid());
    EXPECT_FALSE(e2.isValid());
    EXPECT_TRUE(e3.isValid());
}

TEST(EntityTest, EqualityOperator)
{
    Registry registry;
    Entity e1 = registry.createEntity();
    Entity e2 = e1;

    EXPECT_EQ(e1, e2);

    Entity e3 = registry.createEntity();
    EXPECT_NE(e1, e3);
}