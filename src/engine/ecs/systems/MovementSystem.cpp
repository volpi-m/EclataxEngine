/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** MovementSystem class methods
*/

#include "MovementSystem.hpp"

void ECS::MovementSystem::update(std::unordered_map<unsigned long long, std::shared_ptr<Entity>> &entities)
{
    for (auto &entity : entities) {
        if (entity.second->hasComponent(Flags::transform))
            
    }
}