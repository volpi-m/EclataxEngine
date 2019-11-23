/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Entity class declaration
*/

/// \file Entity.hpp
/// \author Lucas T.
/// \brief Header file for the Entity class

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Logger.hpp"

/// \namespace Client
/// \brief Used for all Client system subclasses
namespace Client {

    /// \class Entity
    /// \brief Entity class, create an entity in the game world
    class Entity {
        public:
            /// \brief constructor
            /// Create an entity with an empty texture
            /// \param rect : Size of the empty texture
            Entity(sf::IntRect &rect);

            /// \brief constructor
            /// Create an entity with an empty texture
            /// \param rect : scale of the empty texture
            Entity(const std::string &filepath, sf::IntRect &rect);

            /// \brief destructor
            /// Destroy the Entity class
            ~Entity() = default;

            /// \return a boolean, true if the entity is visible, false otherwise
            /// \brief Check if the entity is visible
            bool isVisible() const;

            /// \return a boolean, true if the entity is deleted, false otherwise
            /// \brief Check if the entity is deleted
            bool deleted() const;

            /// \return return a bool set to true if the operation is a success, false otherwise
            /// \param filepath : filepath to the texture
            /// \param rect : scale of the texture
            bool loadTexture(const std::string &filepath, sf::IntRect &rect);

            /// \return return a bool set to true if the operation is a success, false otherwise
            /// \param rect : scale of the texture
            bool loadEmptyTexture(sf::IntRect &rect);

            /// \brief return the sprite of the current entity
            /// \return the sprite of the entity
            sf::Sprite &sprite();

        private:

            /*! has the entity been deleted */
            bool _deleted;
            /*! is the entity visible */
            bool _visible;
            /*! the sprite*/
            sf::Sprite _sprite;
            /*! the texture*/
            sf::Texture _texture;
    };
}