//
// Created by tabis on 10/10/2019.
//

#include "DamageComponent.hpp"
#include <gtest/gtest.h>

TEST(DamageComponentsTest, createBasicComponent)
{
    ECS::Component::Damage componentDefault;
    ECS::Component::Damage component(100);

    // Asserting default component and with a set damage value
    ASSERT_EQ(componentDefault.damage, 0);
    ASSERT_EQ(component.damage, 100);
}