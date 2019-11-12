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
        if (entity.second->hasComponent(Flags::transform)) {
            std::cout << "Transform component found. Casting ..." << std::endl;

            auto component = static_cast<ECS::Component::Transform *>(entity.second->component(Flags::transform).get());
            std::cout << "values : " << std::endl;
            std::cout << "x : " << component->x << std::endl;
            std::cout << "y : " << component->y << std::endl;
            std::cout << "z : " << component->z << std::endl;
            std::cout << "Increment x ..." << std::endl;
            component->x++;
        }
}