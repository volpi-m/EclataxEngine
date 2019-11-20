//
// Created by tabis on 10/10/2019.
//

#include "ECS.hpp"
#include "ScriptComponent.hpp"
#include <gtest/gtest.h>

void dummyFunction(std::shared_ptr<ECS::Entity> &entity)
{
    entity->setVisible(false);
}

TEST(ScriptComponentsTest, createBasicComponent)
{
    ECS::Component::Script componentDefault;

    // Attach the script to a component
    ECS::Component::Script component(&dummyFunction);
    Module::EntityComponentSystem ECS;

    auto entity = ECS.createEntity("Entity");
 
    // Checking pointer validity
    ASSERT_EQ(componentDefault.updateScript, nullptr);
    ASSERT_NE(component.updateScript, nullptr);

    // Updating the entity with the script component
    ASSERT_EQ(ECS.isEntityVisible(entity), true);
    component.updateScript(ECS.entity(entity));
    ASSERT_EQ(ECS.isEntityVisible(entity), false);
}