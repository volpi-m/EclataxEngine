/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** MovementSystem class methods
*/

#include "HealthManipulatorSystem.hpp"

void ECS::System::HealthManipulator::update(std::unordered_map<unsigned long long, std::shared_ptr<Entity>> &entities)
{
    for (auto &entity : entities)
        if (entity.second->hasComponent(Component::Flags::health)) {
            // Deleting entities that have no health left
            auto component = static_cast<ECS::Component::Health *>(entity.second->component(Component::Flags::health).get());

            if (component->health <= 0)
                entity.second->deleteEntity();
        }
}

void ECS::System::HealthManipulator::subHealth(std::shared_ptr<Entity> &entity, int health)
{
    // Casting the correct component
    auto component = static_cast<ECS::Component::Health *>(entity->component(Component::Flags::health).get());

    // Substracting healt
    component->health = component->health < health ? 0 : component->health - health;
}

void ECS::System::HealthManipulator::addHealth(std::shared_ptr<Entity> &entity, int health)
{
    // Casting the correct component
    auto component = static_cast<ECS::Component::Health *>(entity->component(Component::Flags::health).get());

    // Adding healt
    component->health = component->health + health > component->healthLimit && component->healthLimit ? component->healthLimit : component->health + health;
}

void ECS::System::HealthManipulator::setHealth(std::shared_ptr<Entity> &entity, int health)
{
    // Casting the correct component
    auto component = static_cast<ECS::Component::Health *>(entity->component(Component::Flags::health).get());

    // setting health
    component->health = health > component->healthLimit && component->healthLimit ? component->healthLimit : health;
}

void ECS::System::HealthManipulator::setHealthLimit(std::shared_ptr<Entity> &entity, int health)
{
    // Casting the correct component
    auto component = static_cast<ECS::Component::Health *>(entity->component(Component::Flags::health).get());

    // setting health limit + rejusting health just in case
    component->healthLimit = health;
    component->health = component->health > component->healthLimit && component->healthLimit ? component->healthLimit : component->health;
}

int ECS::System::HealthManipulator::health(std::shared_ptr<Entity> &entity) const
{
    // Casting the correct component
    auto component = static_cast<ECS::Component::Health *>(entity->component(Component::Flags::health).get());

    return component->health;
}

int ECS::System::HealthManipulator::healthLimit(std::shared_ptr<Entity> &entity) const
{
    // Casting the correct component
    auto component = static_cast<ECS::Component::Health *>(entity->component(Component::Flags::health).get());

    return component->healthLimit;
}