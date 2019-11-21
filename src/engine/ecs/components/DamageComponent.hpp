/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component interface
*/

/// \file DamageComponent.hpp
/// \author Lucas T.
/// \brief DamageComponent class declaration

#pragma once

#include <cstdint>

#include "IComponent.hpp"

/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {
    /// \namespace Component
    /// \brief Used for the all component
    namespace Component {

        /// \struct Damage
        /// \brief Damage structure, create the Damage component
        struct Damage : public IComponent {
            
            /// \brief constructor
            Damage() : damage(0) {}

            /// \brief constructor
            /// \param _damage : damage value 
            Damage(std::size_t _damage) : damage(_damage) {}

            /*! damage attribute */
            std::size_t damage;
        };
    }
}
