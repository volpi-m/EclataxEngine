//
// Created by Someone
//

#include "ECS.hpp"
#include "SpawnerComponent.hpp"
#include <gtest/gtest.h>

TEST(SpawnerComponentsTest, createBasicComponent)
{
    Module::EntityComponentSystem ECS;
    auto entity = ECS.createEntity("new entity");

    ECS::Component::Spawner componentDefault;
    ECS::Component::Spawner component(std::chrono::seconds(2), ECS.entity(entity));

    ASSERT_EQ(componentDefault.seconds, std::chrono::seconds(5));
    ASSERT_EQ(componentDefault.blueprint->tag(), "blueprint");
    ASSERT_EQ(component.seconds, std::chrono::seconds(2));
    ASSERT_EQ(component.blueprint.get(), ECS.entity(entity).get());
}