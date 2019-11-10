/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Game Engine methods
*/

#include "ECS.hpp"

Module::EntityComponentSystem::EntityComponentSystem() : _initialised(true) {}

unsigned long long Module::EntityComponentSystem::createEntity(const std::string &tag)
{
    // Creating an new id for a new entity
    _newId++;
    _entities.emplace(_newId - 1, new ECS::Entity(tag));

    return _newId - 1;
}

unsigned long long Module::EntityComponentSystem::createEntity(const char *tag)
{
    // Creating an new id for a new entity
    _newId++;
    _entities.emplace(_newId - 1, new ECS::Entity(tag));

    return _newId - 1;
}

void Module::EntityComponentSystem::setEntityVisibleState(unsigned long long id, bool state)
{
    _entities[id]->setVisible(state);
}

bool Module::EntityComponentSystem::hasEntity(unsigned long long id) const
{
    return _entities.find(id) == _entities.end();
}

std::string Module::EntityComponentSystem::tag(unsigned long long id)
{
    return _entities[id]->tag();
}

void Module::EntityComponentSystem::update()
{
    // std::async ?
    for (auto &system : _systems)
        system->update(_entities);
}