/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component Acceleration
*/

/// \file Acceleration.hpp
/// \author Someone
/// \brief AccelerationComponent class declaration

#pragma once

#include <cstdint>

#include "IComponent.hpp"

/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {
    /// \namespace Component
    /// \brief Used for the all component
    namespace Component {

        /// \struct Acceleration
        /// \brief Acceleration structure, create the Acceleration component
        struct Acceleration : public IComponent {
            
            /// \brief constructor
            Acceleration() : acceleration(0) {}

            /// \brief constructor
            /// \param _acceleration : acceleration value
            Acceleration(std::size_t _acceleration) : acceleration(_acceleration) {}

            /*! acceleration attribute */
            float acceleration;
        };
    }
}
