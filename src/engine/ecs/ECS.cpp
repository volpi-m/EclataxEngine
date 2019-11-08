/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Game Engine methods
*/

#include "ECS.hpp"

void Module::EntityComponentSystem::update()
{
    // std::async ?
    for (auto &system : _systems)
        system->update(_entities);
}