//
// Created by tabis on 10/10/2019.
//

#include "ECS.hpp"
#include "HealthComponent.hpp"
#include <gtest/gtest.h>

TEST(healtComponentsTest, createBasicComponent)
{
    ECS::Component::Health component;

    ASSERT_EQ(component.health, 1);
    ASSERT_EQ(component.healthLimit, 0);
}