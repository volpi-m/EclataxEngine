//
// Created by Someone
//

#include "ECS.hpp"
#include "SpawnerComponent.hpp"
#include <gtest/gtest.h>

std::shared_ptr<ECS::Entity> dummySp(std::shared_ptr<ECS::Entity> &parent)
{
    (void)parent;
    return std::shared_ptr<ECS::Entity>(new ECS::Entity("blueprint"));
}

TEST(SpawnerComponentsTest, createBasicComponent)
{
    Module::EntityComponentSystem ECS;
    auto entity = ECS.createEntity("new entity");

    ECS::Component::Spawner componentDefault;
    ECS::Component::Spawner component(std::chrono::seconds(2), &dummySp);

    ASSERT_EQ(componentDefault.seconds, std::chrono::seconds(5));
    ASSERT_STREQ(component.createBlueprint(ECS.entity(entity))->tag().c_str(), "blueprint");
    ASSERT_EQ(component.seconds, std::chrono::seconds(2));
}