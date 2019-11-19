/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component interface
*/

/// \file LifeComponent.hpp
/// \author Lucas T.
/// \brief LifeComponent class declaration

#pragma once

#include <cstdint>

#include "IComponent.hpp"

/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {
    /// \namespace Component
    /// \brief Used for the all component
    namespace Component {

        /// \struct Life
        /// \brief Life structure, create the Life component
        struct Health : public IComponent {
            
            /// \brief constructor
            Health() : health(1), healthLimit(0) {}

            /// \brief constructor
            Health(std::size_t _health, std::size_t _healthLimit = 0) : health(_health), healthLimit(_healthLimit) {}

            /*! health attribute */
            std::size_t health;
            /*! health limit attribute (O is unlimited) */
            std::size_t healthLimit;
        };
    }
}
