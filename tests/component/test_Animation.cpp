//
// Created by Someone
//

#include "Animation2DComponent.hpp"
#include <gtest/gtest.h>

TEST(AnimationComponentsTest, createBasicComponent)
{
    Game::Rect rect(10, 10, 10, 10);
    ECS::Component::Animation2D component(std::chrono::milliseconds(10), rect, 50, 32);
    ECS::Component::Animation2D componentDefault;

    ASSERT_EQ(componentDefault.animationTime, std::chrono::milliseconds(1000));
    ASSERT_EQ(componentDefault.rect.top, 0);
    ASSERT_EQ(componentDefault.rect.left, 0);
    ASSERT_EQ(componentDefault.rect.width, 0);
    ASSERT_EQ(componentDefault.rect.height, 0);
    ASSERT_EQ(componentDefault.maximumLeft, 0);
    ASSERT_EQ(componentDefault.offset, 0);

    ASSERT_EQ(component.animationTime, std::chrono::milliseconds(10));
    ASSERT_EQ(component.rect.top, 10);
    ASSERT_EQ(component.rect.left, 10);
    ASSERT_EQ(component.rect.width, 10);
    ASSERT_EQ(component.rect.height, 10);
    ASSERT_EQ(component.maximumLeft, 50);
    ASSERT_EQ(component.offset, 32);
}