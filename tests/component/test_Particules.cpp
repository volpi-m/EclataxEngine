//
// Created by Someone
//

#include "ParticulesComponent.hpp"
#include <gtest/gtest.h>

TEST(ParticulesComponentsTest, createBasicComponent)
{
    ECS::Component::Particules component(100, 50, 25);
    ECS::Component::Particules componentDefault;

    ASSERT_EQ(componentDefault.samples, 10);
    ASSERT_EQ(componentDefault.size, 10);
    ASSERT_EQ(componentDefault.speed, 1);

    ASSERT_EQ(component.samples, 100);
    ASSERT_EQ(component.size, 50);
    ASSERT_EQ(component.speed, 25);
}
