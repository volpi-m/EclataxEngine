/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Entity class methods
*/

/// \file Entity.cpp
/// \author Lucas T.
/// \brief Source file for the Entity class

#include "EntityClient.hpp"

Client::Entity::Entity(sf::IntRect &rect) : _deleted(false), _visible(true)
{
    if (!loadEmptyTexture(rect)) {
        auto log = Debug::Logger::getInstance();

        log->generateDebugMessage(Debug::WARNING, "The texture couldn't be loaded", "Client::Entity::Entity");
    }
}

Client::Entity::Entity(const std::string &filepath, sf::IntRect &rect) : _deleted(false), _visible(true)
{
    if (!loadTexture(filepath, rect)) {
        auto log = Debug::Logger::getInstance();

        log->generateDebugMessage(Debug::WARNING, "The texture couldn't be created", "Client::Entity::Entity");
    }
}

bool Client::Entity::isVisible() const
{
    return _visible;
}

bool Client::Entity::deleted() const
{
    return _deleted;
}

bool Client::Entity::loadTexture(const std::string &filepath, sf::IntRect &rect)
{
    // Loading the texture
    if (!_texture.loadFromFile(filepath, rect))
        return false;

    // Attach the texture to our sprite
    _sprite.setTexture(_texture);
    return true;
}

bool Client::Entity::loadEmptyTexture(sf::IntRect &rect)
{
    // Loading the texture
    if (!_texture.create(rect.width, rect.height))
        return false;

    // Attach the texture to our sprite
    _sprite.setTexture(_texture);
    return true;
}

sf::Sprite &Client::Entity::sprite()
{
    return _sprite;
}