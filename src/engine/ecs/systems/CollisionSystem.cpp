/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** MovementSystem class methods
*/

#include "CollisionSystem.hpp"

void ECS::System::CollisionSystem::update(std::unordered_map<unsigned long long, std::shared_ptr<Entity>> &entities)
{
    for (auto &entity : entities)
        if (entity.second->hasComponent(Component::Flags::collisionBox)) {
            auto component = static_cast<ECS::Component::CollisionBox *>(entity.second->component(Component::Flags::collisionBox).get());
            std::cout << component->rectangle.width << std::endl;
        }
}

bool ECS::System::CollisionSystem::onCollide2D(std::shared_ptr<Entity> &first, std::shared_ptr<Entity> &second)
{
    // Getting both transforms of entities
    auto transformFirst = static_cast<ECS::Component::Transform *>(first->component(Component::Flags::transform).get());
    auto transformSecond = static_cast<ECS::Component::Transform *>(second->component(Component::Flags::transform).get());

    // Getting both collision boxes of entities
    auto collisiontFirst = static_cast<ECS::Component::CollisionBox *>(first->component(Component::Flags::collisionBox).get());
    auto collisiontSecond = static_cast<ECS::Component::CollisionBox *>(second->component(Component::Flags::collisionBox).get());

    // Checking collision between both entities
    if ((transformFirst->x + collisiontFirst->rectangle.left < transformSecond->x + collisiontSecond->rectangle.left + collisiontSecond->rectangle.width) &&
        (transformFirst->x + collisiontFirst->rectangle.left + collisiontFirst->rectangle.width > transformSecond->x + collisiontSecond->rectangle.left) &&
        (transformFirst->y + collisiontFirst->rectangle.top < transformSecond->y + collisiontSecond->rectangle.top + collisiontSecond->rectangle.height) &&
        (transformFirst->y + collisiontFirst->rectangle.top + collisiontFirst->rectangle.height > transformSecond->y + collisiontSecond->rectangle.top))
        return true;
    return false;
}