//
// Created by tabis on 10/10/2019.
//

#include "ECS.hpp"
#include "HealthManipulatorSystem.hpp"
#include <gtest/gtest.h>

TEST(healthManipulatorTests, getHealth)
{
    Module::EntityComponentSystem ECS;
    std::shared_ptr<ECS::IComponent> component(new ECS::Component::Health);
    ECS::System::HealthManipulator system;

    auto entity = ECS.createEntity(std::string("The best entity"));
    ASSERT_EQ(ECS.hasEntity(entity), true);
    ECS.addComponentToEntity(entity, ECS::Component::Flags::health, component);
    ASSERT_EQ(ECS.hasComponent(entity, ECS::Component::Flags::health), true);

    ASSERT_EQ(system.health(ECS.entity(entity)), 1);
    ASSERT_EQ(system.healthLimit(ECS.entity(entity)), 0);
}

TEST(healthManipulatorTests, addHealth)
{
    Module::EntityComponentSystem ECS;
    std::shared_ptr<ECS::IComponent> component(new ECS::Component::Health);
    ECS::System::HealthManipulator system;

    auto entity = ECS.createEntity(std::string("The best entity"));
    ASSERT_EQ(ECS.hasEntity(entity), true);
    ECS.addComponentToEntity(entity, ECS::Component::Flags::health, component);
    ASSERT_EQ(ECS.hasComponent(entity, ECS::Component::Flags::health), true);

    ASSERT_EQ(system.health(ECS.entity(entity)), 1);
    ASSERT_EQ(system.healthLimit(ECS.entity(entity)), 0);

    system.addHealth(ECS.entity(entity), 100);
    
    ASSERT_EQ(system.health(ECS.entity(entity)), 101);
    ASSERT_EQ(system.healthLimit(ECS.entity(entity)), 0);
}

TEST(healthManipulatorTests, subHealth)
{
    Module::EntityComponentSystem ECS;
    std::shared_ptr<ECS::IComponent> component(new ECS::Component::Health);
    ECS::System::HealthManipulator system;

    auto entity = ECS.createEntity(std::string("The best entity"));
    ASSERT_EQ(ECS.hasEntity(entity), true);
    ECS.addComponentToEntity(entity, ECS::Component::Flags::health, component);
    ASSERT_EQ(ECS.hasComponent(entity, ECS::Component::Flags::health), true);

    ASSERT_EQ(system.health(ECS.entity(entity)), 1);
    ASSERT_EQ(system.healthLimit(ECS.entity(entity)), 0);

    system.addHealth(ECS.entity(entity), 100);

    ASSERT_EQ(system.health(ECS.entity(entity)), 101);
    ASSERT_EQ(system.healthLimit(ECS.entity(entity)), 0);

    system.subHealth(ECS.entity(entity), 51);

    ASSERT_EQ(system.health(ECS.entity(entity)), 50);
    ASSERT_EQ(system.healthLimit(ECS.entity(entity)), 0);
}

TEST(healthManipulatorTests, setHealth)
{
    Module::EntityComponentSystem ECS;
    std::shared_ptr<ECS::IComponent> component(new ECS::Component::Health);
    ECS::System::HealthManipulator system;

    auto entity = ECS.createEntity(std::string("The best entity"));
    ASSERT_EQ(ECS.hasEntity(entity), true);
    ECS.addComponentToEntity(entity, ECS::Component::Flags::health, component);
    ASSERT_EQ(ECS.hasComponent(entity, ECS::Component::Flags::health), true);

    ASSERT_EQ(system.health(ECS.entity(entity)), 1);
    ASSERT_EQ(system.healthLimit(ECS.entity(entity)), 0);

    system.setHealth(ECS.entity(entity), 40);

    ASSERT_EQ(system.health(ECS.entity(entity)), 40);
    ASSERT_EQ(system.healthLimit(ECS.entity(entity)), 0);
}

TEST(healthManipulatorTests, setHealthLimit)
{
    Module::EntityComponentSystem ECS;
    std::shared_ptr<ECS::IComponent> component(new ECS::Component::Health);
    ECS::System::HealthManipulator system;

    auto entity = ECS.createEntity(std::string("The best entity"));
    ASSERT_EQ(ECS.hasEntity(entity), true);
    ECS.addComponentToEntity(entity, ECS::Component::Flags::health, component);
    ASSERT_EQ(ECS.hasComponent(entity, ECS::Component::Flags::health), true);

    ASSERT_EQ(system.health(ECS.entity(entity)), 1);
    ASSERT_EQ(system.healthLimit(ECS.entity(entity)), 0);

    system.setHealthLimit(ECS.entity(entity), 40);

    ASSERT_EQ(system.health(ECS.entity(entity)), 1);
    ASSERT_EQ(system.healthLimit(ECS.entity(entity)), 40);

    system.addHealth(ECS.entity(entity), 60);

    ASSERT_EQ(system.health(ECS.entity(entity)), 40);
    ASSERT_EQ(system.healthLimit(ECS.entity(entity)), 40);

    system.setHealth(ECS.entity(entity), 60);

    ASSERT_EQ(system.health(ECS.entity(entity)), 40);
    ASSERT_EQ(system.healthLimit(ECS.entity(entity)), 40);
}

TEST(healthManipulatorTests, updateAndDestroyEntity)
{
    Module::EntityComponentSystem ECS;
    std::shared_ptr<ECS::IComponent> component(new ECS::Component::Health);
    ECS::System::HealthManipulator system;

    auto entity = ECS.createEntity(std::string("The best entity"));
    ASSERT_EQ(ECS.hasEntity(entity), true);
    ECS.addComponentToEntity(entity, ECS::Component::Flags::health, component);
    ASSERT_EQ(ECS.hasComponent(entity, ECS::Component::Flags::health), true);

    ASSERT_EQ(system.health(ECS.entity(entity)), 1);
    ASSERT_EQ(system.healthLimit(ECS.entity(entity)), 0);

    std::unordered_map<unsigned long long, std::shared_ptr<ECS::Entity>> entityMap;

    entityMap.emplace(entity, ECS.entity(entity));
    system.update(entityMap);

    ASSERT_EQ(ECS.entity(entity)->deleted(), false);

    system.setHealth(ECS.entity(entity), 0);
    system.update(entityMap);

    ASSERT_EQ(ECS.entity(entity)->deleted(), true);
}