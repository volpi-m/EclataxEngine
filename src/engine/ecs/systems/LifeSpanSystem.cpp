/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** AnimationSystem class methods
*/

#include "LifeSpanSystem.hpp"

void ECS::System::LifeSpanSystem::update(std::unordered_map<unsigned long long, std::shared_ptr<Entity>> &entities)
{
    for (auto &entity : entities)
        if (entity.second->hasComponent(Component::Flags::lifeSpan)) {

            // Casting the lifeSpan component and getting current time
            auto component = static_cast<ECS::Component::LifeSpan *>(entity.second->component(Component::Flags::lifeSpan).get());
            std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();

            // Animated if the animation time as been reached 
            if (std::chrono::duration_cast<std::chrono::seconds>(t - component->dateOfBirth) >= component->lifeSpan) {

                // deleting the entity
                entity.second->deleteEntity();

                // Deleting children if specified
                if (component->deleteChildren) {

                    auto children = entity.second->children();
                    for (auto &child : children)
                        child->deleteEntity();
                }
            }
        }
}