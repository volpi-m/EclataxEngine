//
// Created by Someone
//

#include "AccelerationComponent.hpp"
#include <gtest/gtest.h>

TEST(AccelerationComponentsTest, createBasicComponent)
{
    ECS::Component::Acceleration component(12);
    ECS::Component::Acceleration componentDefault;

    ASSERT_EQ(componentDefault.acceleration, 0);
    ASSERT_EQ(component.acceleration, 12);
}