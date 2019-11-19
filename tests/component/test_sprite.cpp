//
// Created by tabis on 10/10/2019.
//

#include "ECS.hpp"
#include "SpriteComponent.hpp"
#include <gtest/gtest.h>

TEST(SpriteComponentsTest, createBasicComponent)
{
    ECS::Component::Sprite componentDefault;
    ECS::Component::Sprite component("texture.file");

    ASSERT_EQ(componentDefault.texture, "");
    ASSERT_EQ(componentDefault.loaded, false);
    ASSERT_EQ(component.texture, "texture.file");
    ASSERT_EQ(component.loaded, false);
}