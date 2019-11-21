//
// Created by Someone
//

#include "SpeedComponent.hpp"
#include <gtest/gtest.h>

TEST(SpeedComponentsTest, createBasicComponent)
{
    ECS::Component::Speed component(100);
    ECS::Component::Speed componentDefault;

    ASSERT_EQ(componentDefault.speed, 0);
    ASSERT_EQ(component.speed, 100);
}