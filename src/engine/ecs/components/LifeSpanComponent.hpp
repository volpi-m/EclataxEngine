/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component LifeSpan
*/

/// \file LifeSpan.hpp
/// \author Someone
/// \brief LifeSpanComponent class declaration

#pragma once

#include <chrono>

#include "IComponent.hpp"

/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {
    /// \namespace Component
    /// \brief Used for the all component
    namespace Component {

        /// \struct LifeSpan
        /// \brief LifeSpan structure, create the LifeSpan component
        struct LifeSpan : public IComponent {
            
            /// \brief constructor
            LifeSpan() : dateOfBirth(std::chrono::high_resolution_clock::now()), lifeSpan(10)  {}

            LifeSpan(std::chrono::seconds _lifeSpan) : dateOfBirth(std::chrono::high_resolution_clock::now()), lifeSpan(_lifeSpan)  {}

            /*! time when the component entity is instanciated */
            std::chrono::high_resolution_clock::time_point dateOfBirth;

            std::chrono::seconds lifeSpan;
        };
    }
}
