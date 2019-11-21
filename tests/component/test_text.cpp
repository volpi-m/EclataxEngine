//
// Created by tabis on 10/10/2019.
//

#include "TextComponent.hpp"
#include <gtest/gtest.h>

TEST(SpriteComponentsTest, createBasicComponent)
{
    ECS::Component::Text componentDefault;
    ECS::Component::Text component("Text value");

    ASSERT_EQ(componentDefault.text.empty(), true);
    ASSERT_STREQ(component.text.c_str(), "Text value");
}