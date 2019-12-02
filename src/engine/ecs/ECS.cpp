/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Game Engine methods
*/

#include "ECS.hpp"

Module::EntityComponentSystem::EntityComponentSystem() : _newId(1), _initialised(false)
{
    init();
}

void Module::EntityComponentSystem::addSystem(ECS::flagType type, std::shared_ptr<ECS::ISystem> &system)
{
    if (_systems.find(type) == _systems.end())
        _systems.emplace(type, system);
}

unsigned long long Module::EntityComponentSystem::addEntity(std::shared_ptr<ECS::Entity> &entity)
{
    // Creating an new id for a new entity
    while (_entities.find(_newId) != _entities.end())
        _newId++;
    _entities.emplace(_newId, entity);

    return _newId;
}

unsigned long long Module::EntityComponentSystem::createEntity(const std::string &tag)
{
    // Creating an new id for a new entity
    while (_entities.find(_newId) != _entities.end())
        _newId++;
    _entities.emplace(_newId, new ECS::Entity(tag));

    return _newId;
}

unsigned long long Module::EntityComponentSystem::createEntity(const char *tag)
{
    // Creating an new id for a new entity
    while (_entities.find(_newId) != _entities.end())
        _newId++;
    _entities.emplace(_newId, new ECS::Entity(tag));

    return _newId;
}

unsigned long long Module::EntityComponentSystem::createEntityFromLibrary(const std::string &filepath)
{
    ECS::Entity *ptr = _loader.getInstance<ECS::Entity>(filepath);

    // Checking if the library exists
    if (!ptr) {
        auto log = Debug::Logger::getInstance();

        log->generateDebugMessage(Debug::WARNING, "Couldn't load an entity from a dynamic library.", "Module::EntityComponentSystem::createEntityFromLibrary");
        return 0;
    }

    // Creating an new id for a new entity
    std::shared_ptr<ECS::Entity> newEntity(ptr);
    while (_entities.find(_newId) != _entities.end())
        _newId++;
    _entities.emplace(_newId, newEntity);

    return _newId;
}

unsigned long long Module::EntityComponentSystem::createEntityFromLibrary(const char *filepath)
{
    ECS::Entity *ptr = _loader.getInstance<ECS::Entity>(filepath);

    // Checking if the library exists
    if (!ptr) {
        auto log = Debug::Logger::getInstance();

        log->generateDebugMessage(Debug::WARNING, "Couldn't load an entity from a dynamic library.", "Module::EntityComponentSystem::createEntityFromLibrary");
        return 0;
    }

    // Creating an new id for a new entity
    std::shared_ptr<ECS::Entity> newEntity(ptr);
    while (_entities.find(_newId) != _entities.end())
        _newId++;
    _entities.emplace(_newId, newEntity);

    return _newId;
}

void Module::EntityComponentSystem::deleteEntity(unsigned long long id)
{
    if (_entities.find(id) != _entities.end())
        _entities.erase(id);
}
        

void Module::EntityComponentSystem::addComponentToEntity(unsigned long long id, ECS::flagType flag, std::shared_ptr<ECS::IComponent> &component)
{
    _entities[id]->addComponent(flag, component);
}

void Module::EntityComponentSystem::setEntityVisibleState(unsigned long long id, bool state)
{
    _entities[id]->setVisible(state);
}

bool Module::EntityComponentSystem::isEntityVisible(unsigned long long id)
{
    return _entities[id]->isVisible();
}

bool Module::EntityComponentSystem::hasEntity(unsigned long long id) const
{
    return !(_entities.find(id) == _entities.end());
}

bool Module::EntityComponentSystem::hasComponent(unsigned long long id, ECS::flagType type)
{
    return _entities[id]->hasComponent(type);
}

std::string Module::EntityComponentSystem::tag(unsigned long long id)
{
    return _entities[id]->tag();
}

std::shared_ptr<ECS::ISystem> &Module::EntityComponentSystem::system(ECS::flagType type)
{
    return _systems[type];
}

std::shared_ptr<ECS::Entity> &Module::EntityComponentSystem::entity(unsigned long long id)
{
    return _entities[id];
}

std::size_t Module::EntityComponentSystem::systems() const
{
    return _systems.size();
}

bool Module::EntityComponentSystem::isInitialised()
{
    return _initialised;
}

void Module::EntityComponentSystem::update()
{
    // std::async ?
    for (auto &system : _systems)
        system.second->update(_entities);
}

void Module::EntityComponentSystem::clearEntities()
{
    std::vector<unsigned long long> ids;

    // Searching for deleted entities
    for (auto &entity : _entities)
        if (entity.second->deleted())
            ids.push_back(entity.first);

    // Deleting all entities that are marked as deleted
    for (auto &key : ids)
        _entities.erase(key);
}

std::vector<unsigned long long> Module::EntityComponentSystem::ids()
{
    std::vector<unsigned long long> ids;

    for (auto &entity : _entities)
        ids.push_back(entity.first);
    
    // Sorting ids
    std::sort(ids.begin(), ids.end()); 
    return ids;
}

void Module::EntityComponentSystem::init()
{
    _initialised = true;
}

void Module::EntityComponentSystem::clear()
{
    _entities.clear();
    _systems.clear();
    _newId = 1;
}