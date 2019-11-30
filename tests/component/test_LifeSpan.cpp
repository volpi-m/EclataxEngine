//
// Created by Someone
//

#include "LifeSpanComponent.hpp"
#include <gtest/gtest.h>

TEST(LifeSpanComponentsTest, createBasicComponent)
{
    ECS::Component::LifeSpan component(std::chrono::seconds(5));
    ECS::Component::LifeSpan componentDefault;

    ASSERT_EQ(componentDefault.lifeSpan, std::chrono::seconds(10));
    ASSERT_EQ(component.lifeSpan, std::chrono::seconds(5));
}
