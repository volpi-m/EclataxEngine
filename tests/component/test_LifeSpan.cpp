//
// Created by Someone
//

#include "LifeSpanComponent.hpp"
#include <gtest/gtest.h>

TEST(LifeSpanComponentsTest, createBasicComponent)
{
    ECS::Component::LifeSpan component(std::chrono::seconds(5), true);
    ECS::Component::LifeSpan componentDefault;

    ASSERT_EQ(componentDefault.lifeSpan, std::chrono::seconds(10));
    ASSERT_EQ(componentDefault.deleteChildren, false);
    ASSERT_EQ(component.lifeSpan, std::chrono::seconds(5));
    ASSERT_EQ(component.deleteChildren, true);
}
