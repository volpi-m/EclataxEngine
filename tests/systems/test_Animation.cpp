//
// Created by ArthurLang on 06/04/2020.
//

#include <thread>
#include <gtest/gtest.h>

#include "ECS.hpp"
#include "AnimationSystem.hpp"
#include "AudioComponent.hpp"

TEST(AnimationComponentsTest, updateMethod)
{
    Module::EntityComponentSystem ECS;
    ECL::Rect rect(0, 0, 10, 10);
    std::shared_ptr<ECS::IComponent>component = std::make_shared<ECS::Component::Animation2D>(std::chrono::milliseconds(1), rect, 20, 10);
    std::shared_ptr<ECS::ISystem>animatonSystem = std::make_shared<ECS::System::AnimationSystem>();
    auto entity = ECS.createEntity(std::string("Animated entitie"));

    ECS.addSystem(ECS::Component::Flags::animation2D, animatonSystem);
    ASSERT_EQ(static_cast<ECS::Component::Animation2D *>(component.get())->rect.left, 0);
    ASSERT_EQ(static_cast<ECS::Component::Animation2D *>(component.get())->rect.top, 0);
    ASSERT_EQ(static_cast<ECS::Component::Animation2D *>(component.get())->rect.width, 10);
    ASSERT_EQ(static_cast<ECS::Component::Animation2D *>(component.get())->rect.height, 10);
    ECS.addComponentToEntity(entity, ECS::Component::Flags::animation2D, component);
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    ECS.update();
    ASSERT_EQ(static_cast<ECS::Component::Animation2D *>(component.get())->rect.left, 10);
    ASSERT_EQ(static_cast<ECS::Component::Animation2D *>(component.get())->rect.top, 10);
    ASSERT_EQ(static_cast<ECS::Component::Animation2D *>(component.get())->rect.width, 20);
    ASSERT_EQ(static_cast<ECS::Component::Animation2D *>(component.get())->rect.height, 20);
}