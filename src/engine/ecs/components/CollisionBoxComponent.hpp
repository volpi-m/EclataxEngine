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

        /// \struct CollisionBox
        /// \brief CollisionBox structure, create the CollisionBox components
        struct CollisionBox : public IComponent {
            
            /// \brief constructor
            CollisionBox() {}

            /// \brief constructor
            CollisionBox(float _top, float _left, float _width, float _height) : rectangle(Game::Rect(_top, _left, _width, _height)) {}

            /*! rectangle attribute */
            Game::Rect rectangle;
        };
    }
}
