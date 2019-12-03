/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component interface
*/

/// \file CollisionBox.hpp
/// \author Lucas T.
/// \brief CollisionBox class declaration

#pragma once

#include "IComponent.hpp"
#include "Rect.hpp"

/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {
    /// \namespace Component
    /// \brief Used for the all component
    namespace Component {

        /// \struct CollisionBox2D
        /// \brief CollisionBox structure, create the CollisionBox components
        struct CollisionBox2D : public IComponent {
            
            /// \brief constructor
            CollisionBox2D() : rectangle(Game::Rect(0, 0, 0, 0)) {}

            /// \brief constructor
            CollisionBox2D(float _top, float _left, float _width, float _height) : rectangle(Game::Rect(_top, _left, _width, _height)) {}

            /*! rectangle attribute */
            Game::Rect rectangle;
        };
    }
}
