/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component Speed
*/

/// \file Speed.hpp
/// \author Someone
/// \brief SpeedComponent class declaration

#pragma once

#include <cstdint>

#include "IComponent.hpp"

/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {
    /// \namespace Component
    /// \brief Used for the all component
    namespace Component {

        /// \struct Speed
        /// \brief Speed structure, create the Speed component
        struct Speed : public IComponent {
            
            /// \brief constructor
            Speed() : speed(0) {}

            /// \brief constructor
            /// \param _speed : speed value
            Speed(float _speed) : speed(_speed) {}

            /*! attribute */
            float speed;
        };
    }
}
