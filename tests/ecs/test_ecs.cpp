//
// Created by tabis on 10/10/2019.
//

#include "ECS.hpp"
#include "MovementSystem.hpp"
#include "TransformComponent.hpp"
#include <gtest/gtest.h>

TEST(ECSTests, AddSystemToEcs)
{
    Module::EntityComponentSystem ECS;
    std::unique_ptr<ECS::ISystem> system(new ECS::System::MovementSystem);

    ASSERT_EQ(ECS.isInitialised(), true);
    ASSERT_EQ(ECS.systems(), 0);
    ECS.addSystem(system);
    ECS.update();
    ASSERT_EQ(ECS.systems(), 1);
}

TEST(ECSTests, createEntityInEcs)
{
    Module::EntityComponentSystem ECS;

    auto first = ECS.createEntity(std::string("entity from string"));
    auto second = ECS.createEntity("entity from char");
    ASSERT_EQ(ECS.hasEntity(first), true);
    ASSERT_EQ(ECS.hasEntity(second), true);
    ASSERT_EQ(ECS.hasEntity(3), false);
    ASSERT_STREQ(ECS.tag(first).c_str(), "entity from string");
    ASSERT_STREQ(ECS.tag(second).c_str(), "entity from char");
}

TEST(ECSTests, addAComponentToAnEntity)
{
    Module::EntityComponentSystem ECS;
    std::shared_ptr<ECS::IComponent> component(new ECS::Component::Transform);

    auto entity = ECS.createEntity(std::string("The best entity"));
    ASSERT_EQ(ECS.hasEntity(entity), true);
    ECS.addComponentToEntity(entity, ECS::Flags::transform, component);
    ASSERT_EQ(ECS.hasComponent(entity, ECS::Flags::transform), true);
}

TEST(ECSTests, entityVisibleStates)
{
    Module::EntityComponentSystem ECS;

    auto entity = ECS.createEntity(std::string("The best entity"));
    ASSERT_EQ(ECS.hasEntity(entity), true);
    ASSERT_EQ(ECS.isEntityVisible(entity), true);
    ECS.setEntityVisibleState(entity, false);
    ASSERT_EQ(ECS.isEntityVisible(entity), false);
}