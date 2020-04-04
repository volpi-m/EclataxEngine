//
// Created by tabis on 10/10/2019.
//

#include "CollisionBox2DComponent.hpp"
#include <gtest/gtest.h>

TEST(CollisionBoxComponentsTest, createBasicComponent)
{
    ECS::Component::CollisionBox2D componentDefault;
    ECS::Component::CollisionBox2D component(-110, -110, 220, 220);

    ASSERT_EQ(componentDefault.rectangle.height, 0);
    ASSERT_EQ(componentDefault.rectangle.width, 0);
    ASSERT_EQ(componentDefault.rectangle.left, 0);
    ASSERT_EQ(componentDefault.rectangle.top, 0);
    ASSERT_EQ(component.rectangle.height, 220);
    ASSERT_EQ(component.rectangle.width, 220);
    ASSERT_EQ(component.rectangle.left, -110);
    ASSERT_EQ(component.rectangle.top, -110);
}