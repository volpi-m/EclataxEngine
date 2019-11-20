/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** MovementSystem class methods
*/

#include "IASystem.hpp"

void ECS::System::IASystem::update(std::unordered_map<unsigned long long, std::shared_ptr<Entity>> &entities)
{
    for (auto &entity : entities)
        if (entity.second->hasComponent(Component::Flags::script)) {

            // Casting the script component
            auto component = static_cast<ECS::Component::Script *>(entity.second->component(Component::Flags::script).get());

            // Using the script
            component->updateScript(entity.second);
        }
}