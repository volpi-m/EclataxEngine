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
            Sprite() : texture(""), loaded(false) {}

            /// \brief constructor
            Sprite(const std::string &_texture) : texture(_texture), loaded(false) {}

            /*! texture file attribute */
            std::string texture;
            /*! is loaded attribute */
            bool loaded;
        };
    }
}