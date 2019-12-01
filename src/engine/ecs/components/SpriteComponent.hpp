/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component class
*/

/// \file SpriteComponent.hpp
/// \author Lucas T.
/// \brief SpriteComponent class declaration

#pragma once

#include <string>

#include "IComponent.hpp"
#include "CollisionBox2DComponent.hpp"

/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {
    /// \namespace Component
    /// \brief Used for the all component
    namespace Component {

        /// \struct Sprite
        /// \brief Sprite structure, create the Sprite component
        struct Sprite : public IComponent {

            /// \brief constructor
            Sprite() : texture(""), rect(Game::Rect()), loaded(true) {}

            /// \brief constructor
            Sprite(const std::string &_texture, const Game::Rect &_rect) : texture(_texture), rect(_rect.top, _rect.left, _rect.width, _rect.height), loaded(true) {}

            /*! texture file attribute */
            std::string texture;
            /*! rect of the texture attribute */
            Game::Rect rect;
            /*! is loaded attribute */
            bool loaded;
        };
    }
}