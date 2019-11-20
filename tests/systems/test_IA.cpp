//
// Created by tabis on 10/10/2019.
//

#include "ECS.hpp"
#include "IASystem.hpp"
#include <gtest/gtest.h>

void tagFunction(std::shared_ptr<ECS::Entity> &entity)
{
    entity->setTag("New Tag!");
}

TEST(IASystemTests, update)
{
    Module::EntityComponentSystem ECS;
    std::shared_ptr<ECS::IComponent> component(new ECS::Component::Script(&tagFunction));
    ECS::System::IASystem system;

    // Adding Entity to the system and setting up a script component
    auto entity = ECS.createEntity(std::string("The best entity"));
    ASSERT_EQ(ECS.hasEntity(entity), true);
    ECS.addComponentToEntity(entity, ECS::Component::Flags::script, component);
    ASSERT_EQ(ECS.hasComponent(entity, ECS::Component::Flags::script), true);

    // Creating an unordered map with our entity
    std::unordered_map<unsigned long long, std::shared_ptr<ECS::Entity>> entityMap;

    ASSERT_EQ(ECS.tag(entity), "The best entity");

    // Using the update method on the system : the function changes the entity's tag
    entityMap.emplace(entity, ECS.entity(entity));
    system.update(entityMap);

    // Checking the new tag
    ASSERT_EQ(ECS.tag(entity), "New Tag!");
}