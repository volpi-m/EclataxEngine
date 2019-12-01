/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Entity class methods
*/

/// \file Entity.cpp
/// \author Lucas T.
/// \brief Source file for the Entity class

#include "Entity.hpp"

ECS::Entity::Entity(const std::string &tag) : _tag(tag), _deleted(false), _visible(true) {}

ECS::Entity::Entity(const char *tag) : _tag(tag), _deleted(false), _visible(true) {}

ECS::Entity::Entity(const ECS::Entity &entity) : _tag(entity.tag()), _components({}), _children(entity.children()), _deleted(entity.deleted()), _visible(entity.isVisible()) {}

void ECS::Entity::update()
{

}

void ECS::Entity::addChild(std::shared_ptr<Entity> &child)
{
    _children.push_back(child);
}

void ECS::Entity::addComponent(flagType flag, std::shared_ptr<ECS::IComponent> &component)
{
    _components.emplace(flag, component);
}

std::shared_ptr<ECS::IComponent> ECS::Entity::component(flagType flag)
{
    return _components[flag];
}

std::string ECS::Entity::tag() const
{
    return _tag;
}

void ECS::Entity::setTag(const std::string &tag)
{
    _tag = tag;
}

std::size_t ECS::Entity::childrenSize() const
{
    return _children.size();
}

const std::vector<std::shared_ptr<ECS::Entity>> &ECS::Entity::children() const
{
    return _children;
}

bool ECS::Entity::hasComponent(flagType flag) const
{
    return !(_components.find(flag) == _components.end());
}

bool ECS::Entity::isVisible() const
{
    return _visible;
}

void ECS::Entity::setVisible(bool state)
{
    _visible = state;
}

bool ECS::Entity::deleted() const
{
    return _deleted;
}

void ECS::Entity::deleteEntity()
{
    _deleted = true;
}