//
// Created by tabis on 10/10/2019.
//

#include "ECS.hpp"
#include "CollisionSystem.hpp"
#include "MovementSystem.hpp"
#include <gtest/gtest.h>

TEST(CollisionSystemTests, collisionBetweenTwoEntitiesBasic)
{
    Module::EntityComponentSystem ECS;
    std::shared_ptr<ECS::IComponent> transform1(new ECS::Component::Transform);
    std::shared_ptr<ECS::IComponent> transform2(new ECS::Component::Transform(50, 50, 50));
    std::shared_ptr<ECS::IComponent> collisionBox1(new ECS::Component::CollisionBox2D(-10, -10, 20, 20));
    std::shared_ptr<ECS::IComponent> collisionBox2(new ECS::Component::CollisionBox2D(-10, -10, 20, 20));
    ECS::System::CollisionSystem collisionSystem;
    ECS::System::MovementSystem movementSystem;

    // Adding entities to the system and setting up a transforms and collision box components
    auto entity1 = ECS.createEntity(std::string("The best entity"));
    auto entity2 = ECS.createEntity(std::string("Another entity"));
    ASSERT_EQ(ECS.hasEntity(entity1), true);
    ASSERT_EQ(ECS.hasEntity(entity2), true);
    ECS.addComponentToEntity(entity1, ECS::Component::Flags::transform, transform1);
    ECS.addComponentToEntity(entity1, ECS::Component::Flags::collisionBox2D, collisionBox1);
    ECS.addComponentToEntity(entity2, ECS::Component::Flags::transform, transform2);
    ECS.addComponentToEntity(entity2, ECS::Component::Flags::collisionBox2D, collisionBox2);
    ASSERT_EQ(ECS.hasComponent(entity1, ECS::Component::Flags::transform), true);
    ASSERT_EQ(ECS.hasComponent(entity1, ECS::Component::Flags::collisionBox2D), true);
    ASSERT_EQ(ECS.hasComponent(entity2, ECS::Component::Flags::transform), true);
    ASSERT_EQ(ECS.hasComponent(entity2, ECS::Component::Flags::collisionBox2D), true);

    // Testing collisions (need furthur testing)
    ASSERT_EQ(collisionSystem.onCollide2D(ECS.entity(entity1), ECS.entity(entity2)), false);
    movementSystem.move(ECS.entity(entity1), 40, 40, 40);
    ASSERT_EQ(collisionSystem.onCollide2D(ECS.entity(entity1), ECS.entity(entity2)), true);
}

TEST(CollisionSystemTests, collisionBetweenTwoEntitiesUpper)
{
    Module::EntityComponentSystem ECS;
    std::shared_ptr<ECS::IComponent> transform1(new ECS::Component::Transform(-10, 0, 0));
    std::shared_ptr<ECS::IComponent> transform2(new ECS::Component::Transform(30, 30, 0));
    std::shared_ptr<ECS::IComponent> collisionBox1(new ECS::Component::CollisionBox2D(-25, -25, 50, 50));
    std::shared_ptr<ECS::IComponent> collisionBox2(new ECS::Component::CollisionBox2D(-25, -25, 50, 50));
    ECS::System::CollisionSystem collisionSystem;
    ECS::System::MovementSystem movementSystem;

    // Adding entities to the system and setting up a transforms and collision box components
    auto entity1 = ECS.createEntity(std::string("The best entity"));
    auto entity2 = ECS.createEntity(std::string("Another entity"));
    ASSERT_EQ(ECS.hasEntity(entity1), true);
    ASSERT_EQ(ECS.hasEntity(entity2), true);
    ECS.addComponentToEntity(entity1, ECS::Component::Flags::transform, transform1);
    ECS.addComponentToEntity(entity1, ECS::Component::Flags::collisionBox2D, collisionBox1);
    ECS.addComponentToEntity(entity2, ECS::Component::Flags::transform, transform2);
    ECS.addComponentToEntity(entity2, ECS::Component::Flags::collisionBox2D, collisionBox2);
    ASSERT_EQ(ECS.hasComponent(entity1, ECS::Component::Flags::transform), true);
    ASSERT_EQ(ECS.hasComponent(entity1, ECS::Component::Flags::collisionBox2D), true);
    ASSERT_EQ(ECS.hasComponent(entity2, ECS::Component::Flags::transform), true);
    ASSERT_EQ(ECS.hasComponent(entity2, ECS::Component::Flags::collisionBox2D), true);

    // Testing collisions (need furthur testing)
    ASSERT_EQ(collisionSystem.onCollide2D(ECS.entity(entity1), ECS.entity(entity2)), true);
    movementSystem.move(ECS.entity(entity1), -25, 0, 0);
    ASSERT_EQ(collisionSystem.onCollide2D(ECS.entity(entity1), ECS.entity(entity2)), false);
}

TEST(CollisionSystemTests, collisionBetweenTwoEntitiesOfDifferentHeights)
{
    Module::EntityComponentSystem ECS;
    std::shared_ptr<ECS::IComponent> transform1(new ECS::Component::Transform(100, 40, 0));
    std::shared_ptr<ECS::IComponent> transform2(new ECS::Component::Transform(30, 30, 0));
    std::shared_ptr<ECS::IComponent> collisionBox1(new ECS::Component::CollisionBox2D(-10, -10, 20, 20));
    std::shared_ptr<ECS::IComponent> collisionBox2(new ECS::Component::CollisionBox2D(-5, -5, 10, 10));
    ECS::System::CollisionSystem collisionSystem;
    ECS::System::MovementSystem movementSystem;

    // Adding entities to the system and setting up a transforms and collision box components
    auto entity1 = ECS.createEntity(std::string("The best entity"));
    auto entity2 = ECS.createEntity(std::string("Another entity"));
    ASSERT_EQ(ECS.hasEntity(entity1), true);
    ASSERT_EQ(ECS.hasEntity(entity2), true);
    ECS.addComponentToEntity(entity1, ECS::Component::Flags::transform, transform1);
    ECS.addComponentToEntity(entity1, ECS::Component::Flags::collisionBox2D, collisionBox1);
    ECS.addComponentToEntity(entity2, ECS::Component::Flags::transform, transform2);
    ECS.addComponentToEntity(entity2, ECS::Component::Flags::collisionBox2D, collisionBox2);
    ASSERT_EQ(ECS.hasComponent(entity1, ECS::Component::Flags::transform), true);
    ASSERT_EQ(ECS.hasComponent(entity1, ECS::Component::Flags::collisionBox2D), true);
    ASSERT_EQ(ECS.hasComponent(entity2, ECS::Component::Flags::transform), true);
    ASSERT_EQ(ECS.hasComponent(entity2, ECS::Component::Flags::collisionBox2D), true);

    // Testing collisions (need furthur testing)
    ASSERT_EQ(collisionSystem.onCollide2D(ECS.entity(entity1), ECS.entity(entity2)), false);

    // Only one abscisia of difference before colliding
    movementSystem.move(ECS.entity(entity1), -55, 0, 0);
    ASSERT_EQ(collisionSystem.onCollide2D(ECS.entity(entity1), ECS.entity(entity2)), false);
    
    // Colliding
    movementSystem.move(ECS.entity(entity1), -1, 0, 0);
    ASSERT_EQ(collisionSystem.onCollide2D(ECS.entity(entity1), ECS.entity(entity2)), true);
}


TEST(CollisionSystemTests, update)
{
    Module::EntityComponentSystem ECS;
    std::shared_ptr<ECS::IComponent> collisionBox(new ECS::Component::CollisionBox2D(-10, -10, 20, 20));
    ECS::System::CollisionSystem system;

    // Adding entities to the system and setting up a transforms and collision box components
    auto entity = ECS.createEntity(std::string("The best entity"));
    ASSERT_EQ(ECS.hasEntity(entity), true);
    ECS.addComponentToEntity(entity, ECS::Component::Flags::collisionBox2D, collisionBox);
    ASSERT_EQ(ECS.hasComponent(entity, ECS::Component::Flags::collisionBox2D), true);

    // Creating an unordered map with our entity
    std::unordered_map<unsigned long long, std::shared_ptr<ECS::Entity>> entityMap;

    // Using the update method on the system
    entityMap.emplace(entity, ECS.entity(entity));
    system.update(entityMap);

    // There is nothing to be tested in the update method yet
}