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

// ─── Component Tests ───────────────────────────────────────────────

struct Transform {
    float x, y, z;
};

struct Health {
    int current;
    int max;
};

TEST(EntityRegistryTest, AddAndGetComponent)
{
    Registry reg;
    Entity e = reg.createEntity();
    e.addComponent<Transform>(1.0f, 2.0f, 3.0f);

    EXPECT_TRUE(e.hasComponent<Transform>());
    EXPECT_EQ(e.getComponent<Transform>().x, 1.0f);
    EXPECT_EQ(e.getComponent<Transform>().y, 2.0f);
    EXPECT_EQ(e.getComponent<Transform>().z, 3.0f);
}

TEST(EntityRegistryTest, HasComponentReturnsFalseWhenMissing)
{
    Registry reg;
    Entity e = reg.createEntity();
    EXPECT_FALSE(e.hasComponent<Transform>());
}

TEST(EntityRegistryTest, RemoveComponent)
{
    Registry reg;
    Entity e = reg.createEntity();
    e.addComponent<Transform>(1.0f, 2.0f, 3.0f);
    e.removeComponent<Transform>();
    EXPECT_FALSE(e.hasComponent<Transform>());
}

TEST(EntityRegistryTest, MultipleComponentTypes)
{
    Registry reg;
    Entity e = reg.createEntity();
    e.addComponent<Transform>(1.0f, 2.0f, 3.0f);
    e.addComponent<Health>(50, 100);

    EXPECT_TRUE(e.hasComponent<Transform>());
    EXPECT_TRUE(e.hasComponent<Health>());
    EXPECT_EQ(e.getComponent<Health>().current, 50);
}

TEST(EntityRegistryTest, DestroyRemovesAllComponents)
{
    Registry reg;
    Entity e = reg.createEntity();
    e.addComponent<Transform>(1.0f, 2.0f, 3.0f);
    e.addComponent<Health>(100, 100);
    e.destroy();

    EXPECT_FALSE(e.isValid());
}

TEST(EntityRegistryTest, ComponentsIndependentBetweenEntities)
{
    Registry reg;
    Entity e1 = reg.createEntity();
    Entity e2 = reg.createEntity();

    e1.addComponent<Transform>(1.0f, 0.0f, 0.0f);
    e2.addComponent<Transform>(9.0f, 0.0f, 0.0f);

    EXPECT_EQ(e1.getComponent<Transform>().x, 1.0f);
    EXPECT_EQ(e2.getComponent<Transform>().x, 9.0f);
}