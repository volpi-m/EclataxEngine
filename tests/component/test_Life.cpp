//
// Created by Someone
//

#include "LifeComponent.hpp"
#include <gtest/gtest.h>

TEST(LifeComponentsTest, createBasicComponent)
{
    ECS::Component::Life component(10);
    ECS::Component::Life componentDefault;

    ASSERT_EQ(componentDefault.lifes, 1);
    ASSERT_EQ(component.lifes, 10);
}
