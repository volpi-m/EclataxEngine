/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** MovementSystem class methods
*/

#include "SpawnerSystem.hpp"

void ECS::System::SpawnerSystem::update(std::unordered_map<unsigned long long, std::shared_ptr<Entity>> &entities)
{
    for (auto &entity : entities)
        if (entity.second->hasComponent(Component::Flags::spawner)) {

            // Casting the spawner component and getting current time
            auto component = static_cast<ECS::Component::Spawner *>(entity.second->component(Component::Flags::spawner).get());
            std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();

            // creating a new instance if timer is reached
            if (component->seconds.count() && component->createBlueprint && std::chrono::duration_cast<std::chrono::seconds>(t - component->timeSinceLastSpawn) >= component->seconds) {

                // Reseting time
                component->timeSinceLastSpawn = t;
                // Creating a new child
                auto child = component->createBlueprint(entity.second);
                unsigned long long newId = 0;

                // Assigning it an id and pushing it to our list of entities
                for (auto &entity : entities)
                    newId = entity.first >= newId ? entity.first + 1 : newId;
                entities.emplace(newId, child);
                entity.second->addChild(child);
            }
        }
}

void ECS::System::SpawnerSystem::spawn(std::shared_ptr<Entity> &entity, std::shared_ptr<Module::EntityComponentSystem> &ECS)
{
    // Getting the spawner component
    auto component = static_cast<ECS::Component::Spawner *>(entity->component(ECS::Component::Flags::spawner).get());

    // Using the spawn script
    auto child = component->createBlueprint(entity);
    
    ECS->addEntity(child);
    entity->addChild(child);
}