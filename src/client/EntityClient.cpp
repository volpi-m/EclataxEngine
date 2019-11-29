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

Client::Entity::Entity(sf::Texture &texture) : _deleted(false), _visible(true), _textureIdx(0)
{
    _sprite.setTexture(texture);
}

Client::Entity::Entity(sf::Texture &texture, std::size_t textureIdx) : _deleted(false), _visible(true), _textureIdx(textureIdx)
{
    _sprite.setTexture(texture);
}

bool Client::Entity::isVisible() const
{
    return _visible;
}

bool Client::Entity::deleted() const
{
    return _deleted;
}

sf::Sprite &Client::Entity::sprite()
{
    return _sprite;
}

std::size_t Client::Entity::textureIdx()
{
    return _textureIdx;
}

void Client::Entity::setTextureIdx(std::size_t textureIdx, sf::Texture &texture)
{
    // Checking if the entity already as set the texture passed as parameter
    if (textureIdx == _textureIdx)
        return;

    // If not, set the texture
    _sprite.setTexture(texture);
    _textureIdx = textureIdx;    
}

void Client::Entity::setPosition(float x, float y, [[maybe_unused]] float z)
{
    _sprite.setPosition(sf::Vector2f(x, y));
}

void Client::Entity::setTextureRect(float top, float left, float width, float heigth)
{
    _sprite.setTextureRect(sf::IntRect(left, top, width, heigth));
}