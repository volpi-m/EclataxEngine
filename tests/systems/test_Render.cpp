//
// Created by tabis on 10/10/2019.
//

#include "ECS.hpp"
#include "RenderSystem.hpp"
#include <gtest/gtest.h>


TEST(RenderSystemTests, update)
{
    Module::EntityComponentSystem ECS;
    std::shared_ptr<ECS::IComponent> component(new ECS::Component::Sprite);
    ECS::System::RenderSystem system;

    // Adding Entity to the system and setting up a sprite component
    auto entity = ECS.createEntity(std::string("The best entity"));
    ASSERT_EQ(ECS.hasEntity(entity), true);
    ECS.addComponentToEntity(entity, ECS::Component::Flags::sprite, component);
    ASSERT_EQ(ECS.hasComponent(entity, ECS::Component::Flags::sprite), true);

    // Creating an unordered map with our entity
    std::unordered_map<unsigned long long, std::shared_ptr<ECS::Entity>> entityMap;

    // Using the update method on the system
    entityMap.emplace(entity, ECS.entity(entity));
    system.update(entityMap);

    // There is nothing to be tested in the update method yet
}

TEST(RenderSystemTests, getTexture)
{
    Module::EntityComponentSystem ECS;
    Game::Rect rect(0, 0, 32, 32);
    std::shared_ptr<ECS::IComponent> componentDefault(new ECS::Component::Sprite);
    std::shared_ptr<ECS::IComponent> component(new ECS::Component::Sprite("New texture!", rect));
    ECS::System::RenderSystem system;

    // Creating two entities
    auto entity1 = ECS.createEntity(std::string("The best entity"));
    auto entity2 = ECS.createEntity(std::string("The most best entity"));

    // Assigning two sprite components to the entities, one without texture and another with it
    ASSERT_EQ(ECS.hasEntity(entity1), true);
    ASSERT_EQ(ECS.hasEntity(entity2), true);
    ECS.addComponentToEntity(entity1, ECS::Component::Flags::sprite, componentDefault);
    ECS.addComponentToEntity(entity2, ECS::Component::Flags::sprite, component);
    ASSERT_EQ(ECS.hasComponent(entity1, ECS::Component::Flags::sprite), true);
    ASSERT_EQ(ECS.hasComponent(entity2, ECS::Component::Flags::sprite), true);

    // Checking the textures
    ASSERT_EQ(system.texture(ECS.entity(entity1)), "");
    ASSERT_EQ(system.texture(ECS.entity(entity2)), "New texture!");
}

TEST(RenderSystemTests, setTexture)
{
    Module::EntityComponentSystem ECS;
    Game::Rect rect(0, 0, 32, 32);
    std::shared_ptr<ECS::IComponent> component(new ECS::Component::Sprite("New texture!", rect));
    ECS::System::RenderSystem system;

    // Creating an entity
    auto entity = ECS.createEntity(std::string("The best entity"));

    // Setting up a sprite component
    ASSERT_EQ(ECS.hasEntity(entity), true);
    ECS.addComponentToEntity(entity, ECS::Component::Flags::sprite, component);
    ASSERT_EQ(ECS.hasComponent(entity, ECS::Component::Flags::sprite), true);

    // Testing if we can change textures
    ASSERT_EQ(system.texture(ECS.entity(entity)), "New texture!");
    system.setTexture(ECS.entity(entity), "Changed texture!");
    ASSERT_EQ(system.texture(ECS.entity(entity)), "Changed texture!");
}

TEST(RenderSystemTests, setLoaded)
{
    Game::Rect rect(0, 0, 32, 32);
    Module::EntityComponentSystem ECS;
    std::shared_ptr<ECS::IComponent> component(new ECS::Component::Sprite("New texture!", rect));
    ECS::System::RenderSystem system;

    // Creating an entity
    auto entity = ECS.createEntity(std::string("The best entity"));

    // Setting up a sprite component
    ASSERT_EQ(ECS.hasEntity(entity), true);
    ECS.addComponentToEntity(entity, ECS::Component::Flags::sprite, component);
    ASSERT_EQ(ECS.hasComponent(entity, ECS::Component::Flags::sprite), true);

    // Testing if texture as been loaded
    ASSERT_EQ(system.loaded(ECS.entity(entity)), false);
    system.setLoaded(ECS.entity(entity));
    ASSERT_EQ(system.loaded(ECS.entity(entity)), true);
}