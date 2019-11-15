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
        struct Life : public IComponent {
            
            /// \brief constructor
            Life() : life(0) {}

            /// \brief constructor
            Life(std::size_t _life) :life(_life) {}

            /*! life attribute */
            std::size_t life;
        };
    }
}
