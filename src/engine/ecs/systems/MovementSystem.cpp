/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** MovementSystem class methods
*/

#include "MovementSystem.hpp"

void ECS::System::MovementSystem::update(std::unordered_map<unsigned long long, std::shared_ptr<Entity>> &entities)
{
    for (auto &entity : entities)
        if (entity.second->hasComponent(Component::Flags::transform)) {
            // OK
        }
}

std::tuple<float, float, float> ECS::System::MovementSystem::transform(const std::shared_ptr<Entity> &entity) const
{
    // Casting it to the correct component
    auto component = static_cast<ECS::Component::Transform *>(entity->component(Component::Flags::transform).get());

    // Modifying the component of the current entity
    return std::make_tuple(component->x, component->y, component->z);
}

void ECS::System::MovementSystem::setTransform(std::shared_ptr<Entity> &entity, float x, float y, float z)
{
    // Casting it to the correct component
    auto component = static_cast<ECS::Component::Transform *>(entity->component(Component::Flags::transform).get());

    // Modifying the component of the current entity
    component->x = x;
    component->y = y;
    component->z = z;
}

void ECS::System::MovementSystem::move(std::shared_ptr<Entity> &entity, float x, float y, float z)
{
    // Casting it to the correct component
    auto component = static_cast<ECS::Component::Transform *>(entity->component(Component::Flags::transform).get());

    // Modifying the component of the current entity
    component->x += x;
    component->y += y;
    component->z += z;
}

float ECS::System::MovementSystem::speed(const std::shared_ptr<Entity> &entity)
{
    // Casting it to the correct component
    auto component = static_cast<ECS::Component::Speed *>(entity->component(Component::Flags::speed).get());

    return component->speed;
}