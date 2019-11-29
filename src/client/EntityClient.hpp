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

namespace Client {

    /// \class Entity
    /// \brief Entity class, create an entity in the game world
    class Entity {
        public:
            /// \brief constructor
            /// Create an entity with an empty texture
            /// \param texture : the empty texture of the entity
            Entity(sf::Texture &texture);

            /// \brief constructor
            /// Create an entity with an empty texture
            /// \param texture : the texture of the entity
            /// \param textureIdx : id of the texture
            Entity(sf::Texture &texture, std::size_t textureIdx);

            /// \brief destructor
            /// Destroy the Entity class
            ~Entity() = default;

            /// \return a boolean, true if the entity is visible, false otherwise
            /// \brief Check if the entity is visible
            bool isVisible() const;

            /// \return a boolean, true if the entity is deleted, false otherwise
            /// \brief Check if the entity is deleted
            bool deleted() const;

            /// \brief return the sprite of the current entity
            /// \return the sprite of the entity
            sf::Sprite &sprite();

            /// \brief return the texture index of the current entity
            /// \return the texture index of the entity
            std::size_t textureIdx();

            /// \brief set the texture of the entity
            /// \param textureIdx : the new texture index of the entity
            /// \param texture : the new texture
            void setTextureIdx(std::size_t textureIdx, sf::Texture &texture);

            /// \brief set the position of the entity
            /// \param x : x coordinates
            /// \param y : y coordinates
            /// \param z : z coordinates
            void setPosition(float x, float y, float z);

            /// \brief set the position of the entity
            /// \param top : top position of the rectangle
            /// \param left : left position of the rectangle
            /// \param width : width position of the rectangle
            /// \param heigth : heigth position of the rectangle
            void setTextureRect(float top, float left, float width, float heigth);

        private:

            /*! has the entity been deleted */
            bool _deleted;
            /*! is the entity visible */
            bool _visible;
            /*! the sprite*/
            sf::Sprite _sprite;
            /*! the texture id */
            std::size_t _textureIdx;
            /*! the rect of the texture */
            sf::IntRect _rect;
    };
}