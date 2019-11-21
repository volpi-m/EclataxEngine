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
            if (component->updateScript)
                component->updateScript(entity.second);
        }
}

void ECS::System::IASystem::setScript(std::shared_ptr<Entity> &entity, void (*func)(std::shared_ptr<ECS::Entity> &entity))
{
    // Casting the script component
    auto component = static_cast<ECS::Component::Script *>(entity->component(Component::Flags::script).get());
    
    // if not null assign the pointer
    if (func)
        component->updateScript = func;
}

void ECS::System::IASystem::deleteScript(std::shared_ptr<Entity> &entity)
{
    // Casting the script component
    auto component = static_cast<ECS::Component::Script *>(entity->component(Component::Flags::script).get());
    
    // Assigning pointer to null
    if (component->updateScript)
        component->updateScript = nullptr;
}