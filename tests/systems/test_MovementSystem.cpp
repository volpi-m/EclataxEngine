//
// Created by ArthurLang on 07/04/2020.
//

#include <gtest/gtest.h>

#include "ECS.hpp"
#include "MovementSystem.hpp"
#include "TransformComponent.hpp"

TEST(MovementSystemTest, transformMethod)
{
    Module::EntityComponentSystem ECS;
    std::shared_ptr<ECS::IComponent>component = std::make_shared<ECS::Component::Transform>(0, 0, 0);
    ECS::System::MovementSystem MovementSystem;
    auto entity = ECS.createEntity(std::string("Movable entitie"));
    ECS.addComponentToEntity(entity, ECS::Component::Flags::transform, component);

    std::tuple<float, float, float> tuple = {0, 0, 0};

    ASSERT_EQ(MovementSystem.transform(ECS.entity(entity)), tuple);
}

TEST(MovementSystemTest, setTransformMethod)
{
    Module::EntityComponentSystem ECS;
    std::shared_ptr<ECS::IComponent>component = std::make_shared<ECS::Component::Transform>(0, 0, 0);
    ECS::System::MovementSystem MovementSystem;
    auto entity = ECS.createEntity(std::string("Movable entitie"));
    ECS.addComponentToEntity(entity, ECS::Component::Flags::transform, component);

    std::tuple<float, float, float> tuple = {0, 0, 0};
    ASSERT_EQ(MovementSystem.transform(ECS.entity(entity)), tuple);

    MovementSystem.setTransform(ECS.entity(entity), 1, 0, 0);
    tuple = {1, 0, 0};
    ASSERT_EQ(MovementSystem.transform(ECS.entity(entity)), tuple);
    MovementSystem.setTransform(ECS.entity(entity), 10, 4, -3.9);
    tuple = {10, 4, -3.9};
    ASSERT_EQ(MovementSystem.transform(ECS.entity(entity)), tuple);
}

TEST(MovementSystemTest, moveMethod)
{
    Module::EntityComponentSystem ECS;
    std::shared_ptr<ECS::IComponent>component = std::make_shared<ECS::Component::Transform>(0, 0, 0);
    ECS::System::MovementSystem MovementSystem;
    auto entity = ECS.createEntity(std::string("Movable entitie"));
    ECS.addComponentToEntity(entity, ECS::Component::Flags::transform, component);

    std::tuple<float, float, float> tuple = {0, 0, 0};
    ASSERT_EQ(MovementSystem.transform(ECS.entity(entity)), tuple);

    MovementSystem.move(ECS.entity(entity), 1, 0, 0);
    tuple = {1, 0, 0};
    ASSERT_EQ(MovementSystem.transform(ECS.entity(entity)), tuple);
    MovementSystem.move(ECS.entity(entity), 10, 4, -3.9);
    tuple = {11, 4, -3.9};
    ASSERT_EQ(MovementSystem.transform(ECS.entity(entity)), tuple);
}

TEST(MovementSystemTest, speedMethod)
{
    Module::EntityComponentSystem ECS;
    std::shared_ptr<ECS::IComponent>transform = std::make_shared<ECS::Component::Transform>(0, 0, 0);
    std::shared_ptr<ECS::IComponent>speed = std::make_shared<ECS::Component::Speed>(3);
    ECS::System::MovementSystem MovementSystem;
    auto entity = ECS.createEntity(std::string("Movable entitie"));
    ECS.addComponentToEntity(entity, ECS::Component::Flags::transform, transform);
    ECS.addComponentToEntity(entity, ECS::Component::Flags::speed, speed);

    ASSERT_EQ(MovementSystem.speed(ECS.entity(entity)), 3);
}