//
// Created by tabis on 10/10/2019.
//

#include "ECS.hpp"
#include "SpriteComponent.hpp"
#include <gtest/gtest.h>

TEST(SpriteComponentsTest, createBasicComponent)
{
    Game::Rect rect(0, 0, 32, 32);
    ECS::Component::Sprite componentDefault;
    ECS::Component::Sprite component("texture.file", rect);

    ASSERT_EQ(componentDefault.texture, "");
    ASSERT_EQ(componentDefault.loaded, false);
    ASSERT_EQ(componentDefault.rect.left, 0);
    ASSERT_EQ(componentDefault.rect.top, 0);
    ASSERT_EQ(componentDefault.rect.width, 0);
    ASSERT_EQ(componentDefault.rect.height, 0);

    ASSERT_EQ(component.texture, "texture.file");
    ASSERT_EQ(component.loaded, false);
    ASSERT_EQ(component.rect.left, 0);
    ASSERT_EQ(component.rect.top, 0);
    ASSERT_EQ(component.rect.width, 32);
    ASSERT_EQ(component.rect.height, 32);
}