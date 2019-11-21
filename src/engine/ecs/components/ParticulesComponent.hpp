/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component Particules
*/

/// \file Particules.hpp
/// \author Someone
/// \brief ParticulesComponent class declaration

#pragma once

#include <cstdint>

#include "IComponent.hpp"

/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {
    /// \namespace Component
    /// \brief Used for the all component
    namespace Component {

        /// \struct Particules
        /// \brief Particules structure, create the Particules component
        struct Particules : public IComponent {
            
            /// \brief constructor
            Particules() : samples(10), size(10), speed(1) {}

            /// \brief constructor
            Particules(std::size_t _samples, std::size_t _size, std::size_t _speed) : samples(_samples), size(_size), speed(_speed) {}

            /*! samples attribute */
            std::size_t samples;
            /*! size attribute */
            std::size_t size;
            /*! speed attribute */
            std::size_t speed;
        };
    }
}
