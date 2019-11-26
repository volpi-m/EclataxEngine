/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** EntityFactory class methods
*/

/// \file EntityFactory.cpp
/// \author Lucas T.
/// \brief Source file for the EntityFactory class

#include "EntityFactory.hpp"

bool ECS::EntityFactory::hasEntity(const std::string &key)
{
    return !(_blueprints.find(key) == _blueprints.end());
}

void ECS::EntityFactory::registerEntity(const std::string &key, ECS::Entity &entity)
{
    // if the entity blueprint doesn't exists, we create an new one
    if (_blueprints.find(key) != _blueprints.end())
        return;
        
    // Creating a new empty entity from types given by the entity ref
    _blueprints.emplace(key, Entity(entity));
    unsigned int i = 0;

    // Iterating over flags and adding them if found in the entity to copy
    for (auto &it : _flags) {
        if (entity.hasComponent(it)) {

            // Component found, creating a new empty one in the new entity
            auto newComponent = _emptyComponentFactory[i]();
            _blueprints.at(key).addComponent(it, newComponent);
        }
        ++i;
    }
}

void ECS::EntityFactory::registerEntity(const std::string &key, ECS::flagType types)
{
    // if the entity blueprint doesn't exists, we create an new one
    if (_blueprints.find(key) != _blueprints.end())
        return;

    // Creating a new empty entity from types given by the entity ref
    unsigned int i = 0;
    _blueprints.emplace(key, Entity("Blueprint"));

    // Checking all components
    for (auto it : _flags) {

        // If the component is requested, we add it to the entity using the factory
        if (types & it) {
            auto newComponent = _emptyComponentFactory[i]();
            _blueprints.at(key).addComponent(it, newComponent);
        }
        ++i;
    }
}

std::shared_ptr<ECS::Entity> ECS::EntityFactory::createEntity(const std::string &key)
{
    // if the entity blueprint doesn't exists, we create an new one
    if (_blueprints.find(key) == _blueprints.end())
        return nullptr;

    // Creating a new empty entity from types given by the entity ref
    unsigned int i = 0;
    Entity cpy = _blueprints.at(key);
    std::shared_ptr<Entity> newEntity(new Entity(cpy));
    
    // Iterating over flags and adding them if found in the entity to copy
    for (auto &it : _flags) {
        if (_blueprints.at(key).hasComponent(it)) {
            // Component found, creating a new empty one in the new entity
            auto newComponent = _emptyComponentFactory[i]();
            newEntity->addComponent(it, newComponent);
        }
        ++i;
    }
    return newEntity;
}

// Copy an entity and only the components specified in the types argument
std::shared_ptr<ECS::Entity> ECS::EntityFactory::createEntity(ECS::Entity &entity, ECS::flagType types)
{
    std::shared_ptr<Entity> newEntity(new Entity("Blueprint"));
    unsigned int i = 0;

    // Checking all components
    for (auto it : _flags) {

        // If the component is requested, we add it to the entity using the factory
        if (entity.hasComponent(it)) {

            // Creating an empty component if the flag asen't been specified, copying otherwise
            auto newComponent = (types & it) ? _copyComponentFactory[i](entity.component(it)) : _emptyComponentFactory[i]();
            newEntity->addComponent(it, newComponent);
        }
        ++i;
    }
    return newEntity;
}