/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component Life
*/

/// \file Life.hpp
/// \author Someone
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
        struct Life : public IComponent {
            
            /// \brief constructor
            Life() : lifes(1) {}

            /// \brief constructor
            /// \param _lifes : number of life of the entity
            Life(std::size_t _lifes) : lifes(_lifes) {}

            /*! attribute */
            std::size_t lifes;
        };
    }
}
