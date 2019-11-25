//
// Created by tabis on 10/10/2019.
//

#include "Entity.hpp"
#include "TransformComponent.hpp"
#include <gtest/gtest.h>

TEST(EntityTests, EntityInstance)
{
    ECS::Entity first(std::string("entity from string"));
    ECS::Entity second(std::string("entity from char"));
    ECS::Entity third(second);

    first.update();
    second.update();
    ASSERT_STREQ(first.tag().c_str(), "entity from string");
    ASSERT_STREQ(second.tag().c_str(), "entity from char");
    ASSERT_STREQ(second.tag().c_str(), "entity from char");
    first.setTag("new tag!");
    ASSERT_STREQ(first.tag().c_str(), "new tag!");
}

TEST(EntityTests, EntityAddChild)
{
    ECS::Entity first(std::string("entity from string"));
    std::shared_ptr<ECS::Entity> second(new ECS::Entity(std::string("entity from char")));

    ASSERT_EQ(first.childrenSize(), 0);
    first.addChild(second);
    ASSERT_EQ(first.childrenSize(), 1);
}

TEST(EntityTests, addComponentToEntity)
{
    std::shared_ptr<ECS::IComponent> component(new ECS::Component::Transform);
    ECS::Entity first(std::string("entity from string"));

    first.addComponent(ECS::Component::Flags::transform, component);
    ASSERT_EQ(first.hasComponent(ECS::Component::Flags::transform), true);
    ASSERT_NE(first.component(ECS::Component::Flags::transform).get(), nullptr);
}

TEST(EntityTests, entityVisibleStates)
{
    ECS::Entity first(std::string("entity from string"));

    ASSERT_EQ(first.isVisible(), true);
    first.setVisible(false);
    ASSERT_EQ(first.isVisible(), false);
}

TEST(EntityTests, deleteEntity)
{
    ECS::Entity first(std::string("entity from string"));

    ASSERT_EQ(first.deleted(), false);
    first.deleteEntity();
    ASSERT_EQ(first.deleted(), true);
}

TEST(EntityTests, deleteEntityAndChildren)
{
    ECS::Entity first(std::string("entity from string"));
    std::shared_ptr<ECS::Entity> second(new ECS::Entity(std::string("entity from char")));

    ASSERT_EQ(first.childrenSize(), 0);
    first.addChild(second);
    ASSERT_EQ(first.childrenSize(), 1);
    ASSERT_EQ(first.deleted(), false);
    ASSERT_EQ(second->deleted(), false);
    first.deleteEntity();
    ASSERT_EQ(first.deleted(), true);
    ASSERT_EQ(second->deleted(), true);
}