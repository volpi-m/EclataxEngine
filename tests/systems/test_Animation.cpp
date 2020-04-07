//
// Created by ArthurLang on 06/04/2020.
//

#include <thread>
#include <gtest/gtest.h>

#include "ECS.hpp"
#include "AnimationSystem.hpp"
#include "AudioComponent.hpp"

TEST(AnimationSystemTest, updateMethod)
{
    Module::EntityComponentSystem ECS;
    ECL::Rect rect(0, 0, 10, 10);
    std::shared_ptr<ECS::IComponent>component = std::make_shared<ECS::Component::Animation2D>(std::chrono::milliseconds(1), rect, 30, 10);
    std::shared_ptr<ECS::ISystem>animatonSystem = std::make_shared<ECS::System::AnimationSystem>();
    auto entity = ECS.createEntity(std::string("Animated entitie"));
    ECS.addSystem(ECS::System::Flags::Animation, animatonSystem);
    ECS.addComponentToEntity(entity, ECS::Component::Flags::animation2D, component);

    auto animationComponent = static_cast<ECS::Component::Animation2D *>
        (ECS.entity(entity)->component(ECS::Component::Flags::animation2D).get());

    ASSERT_EQ(animationComponent->rect.left, 0);
    ASSERT_EQ(animationComponent->rect.top, 0);
    ASSERT_EQ(animationComponent->rect.width, 10);
    ASSERT_EQ(animationComponent->rect.height, 10);
    ASSERT_EQ(animationComponent->offset, 10);
    ASSERT_EQ(animationComponent->maximumLeft, 30);
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    ECS.update();
    ASSERT_EQ(animationComponent->rect.left, 10);
    ASSERT_EQ(animationComponent->rect.top, 0);
    ASSERT_EQ(animationComponent->rect.width, 10);
    ASSERT_EQ(animationComponent->rect.height, 10);

}