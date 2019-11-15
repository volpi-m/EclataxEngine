/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component interface
*/

/// \file TransformComponent.hpp
/// \author Lucas T.
/// \brief TransformComponent class declaration

#pragma once

#include <cstdint>

#include "IComponent.hpp"

/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {
    /// \namespace Component
    /// \brief Used for the all component
    namespace Component {

        /// \struct Transform
        /// \brief Transform structure, create the transform components
        struct Transform : public IComponent {
            
            /// \brief constructor
            Transform() : x(0), y(0), z(0) {}

            /// \brief constructor
            Transform(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

            /*! x axis attribute */
            float x; // float
            /*! y axis attribute */
            float y;
            /*! z axis attribute */
            float z;
        };
    }
}
