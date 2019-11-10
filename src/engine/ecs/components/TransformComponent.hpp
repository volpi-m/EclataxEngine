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

    /// \struct Transform
    /// \brief Transform structure, create the transform components
    struct Transform : public IComponent {
        
        /// \brief constructor
        Transform() : x(0), y(0), z(0) {}
        
        /*! x axis attribute */
        std::size_t x;
        /*! y axis attribute */
        std::size_t y;
        /*! z axis attribute */
        std::size_t z;
    };
}
