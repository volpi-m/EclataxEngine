/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** MovementSystem class methods
*/

#include "CollisionSystem.hpp"

void ECS::System::CollisionSystem::update(std::unordered_map<unsigned long long, std::shared_ptr<Entity>> &entities)
{
    (void)entities;
}

bool ECS::System::CollisionSystem::onCollide2D(std::shared_ptr<Entity> &first, std::shared_ptr<Entity> &second)
{
    // Getting both transforms of entities
    auto transformFirst = static_cast<ECS::Component::Transform *>(first->component(Component::Flags::transform).get());
    auto transformSecond = static_cast<ECS::Component::Transform *>(second->component(Component::Flags::transform).get());

    // Getting both collision boxes of entities
    auto collisiontFirst = static_cast<ECS::Component::CollisionBox2D *>(first->component(Component::Flags::collisionBox2D).get());
    auto collisiontSecond = static_cast<ECS::Component::CollisionBox2D *>(second->component(Component::Flags::collisionBox2D).get());

    // Checking collision between both entities
    if ((transformFirst->x + collisiontFirst->rectangle.left < transformSecond->x + collisiontSecond->rectangle.left + collisiontSecond->rectangle.width) &&
        (transformFirst->x + collisiontFirst->rectangle.left + collisiontFirst->rectangle.width > transformSecond->x + collisiontSecond->rectangle.left) &&
        (transformFirst->y + collisiontFirst->rectangle.top < transformSecond->y + collisiontSecond->rectangle.top + collisiontSecond->rectangle.height) &&
        (transformFirst->y + collisiontFirst->rectangle.top + collisiontFirst->rectangle.height > transformSecond->y + collisiontSecond->rectangle.top))
        return true;
    return false;
}

void ECS::System::CollisionSystem::onCollideDamage2D(std::shared_ptr<Entity> &first, std::shared_ptr<Entity> &second)
{
    // Checking all components
    if (!first->hasComponent(ECS::Component::Flags::transform) || !first->hasComponent(ECS::Component::Flags::collisionBox2D) ||
    !first->hasComponent(ECS::Component::Flags::health) || !first->hasComponent(ECS::Component::Flags::damage))
        return;
    if (!second->hasComponent(ECS::Component::Flags::transform) || !second->hasComponent(ECS::Component::Flags::collisionBox2D) ||
    !second->hasComponent(ECS::Component::Flags::health) || !second->hasComponent(ECS::Component::Flags::damage))
        return;

    // Getting both transforms of entities
    auto transformFirst = static_cast<ECS::Component::Transform *>(first->component(Component::Flags::transform).get());
    auto transformSecond = static_cast<ECS::Component::Transform *>(second->component(Component::Flags::transform).get());

    // Getting both collision boxes of entities
    auto collisiontFirst = static_cast<ECS::Component::CollisionBox2D *>(first->component(Component::Flags::collisionBox2D).get());
    auto collisiontSecond = static_cast<ECS::Component::CollisionBox2D *>(second->component(Component::Flags::collisionBox2D).get());

    // Checking collision between both entities
    if ((transformFirst->x + collisiontFirst->rectangle.left < transformSecond->x + collisiontSecond->rectangle.left + collisiontSecond->rectangle.width) &&
        (transformFirst->x + collisiontFirst->rectangle.left + collisiontFirst->rectangle.width > transformSecond->x + collisiontSecond->rectangle.left) &&
        (transformFirst->y + collisiontFirst->rectangle.top < transformSecond->y + collisiontSecond->rectangle.top + collisiontSecond->rectangle.height) &&
        (transformFirst->y + collisiontFirst->rectangle.top + collisiontFirst->rectangle.height > transformSecond->y + collisiontSecond->rectangle.top)) {

            // Getting health and damage components
            auto HealthFirst = static_cast<ECS::Component::Health *>(first->component(Component::Flags::health).get());
            auto HealthSecond = static_cast<ECS::Component::Health *>(second->component(Component::Flags::health).get());
            auto DamageFirst = static_cast<ECS::Component::Damage *>(first->component(Component::Flags::damage).get());
            auto DamageSecond = static_cast<ECS::Component::Damage *>(second->component(Component::Flags::damage).get());

            HealthFirst->health -= DamageSecond->damage;
            HealthSecond->health -= DamageFirst->damage;
    }
}