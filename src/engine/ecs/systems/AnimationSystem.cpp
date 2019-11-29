/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** AnimationSystem class methods
*/

#include "AnimationSystem.hpp"

void ECS::System::AnimationSystem::update(std::unordered_map<unsigned long long, std::shared_ptr<Entity>> &entities)
{
    for (auto &entity : entities)
        if (entity.second->hasComponent(Component::Flags::animation2D)) {

            // Casting the animation component and getting current time
            auto component = static_cast<ECS::Component::Animation2D *>(entity.second->component(Component::Flags::animation2D).get());
            std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();

            // Animated if the animation time as been reached 
            if (std::chrono::duration_cast<std::chrono::milliseconds>(t - component->lastAnimationTime) >= component->animationTime) {

                // Reseting time
                component->lastAnimationTime = t;

                // Updating the sprite sheet
                if (component->rect.left < component->maximumLeft)
                    component->rect.left += component->offset;
                else
                    component->rect.left = 0;
            }
        }
}