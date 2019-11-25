/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component interface
*/

/// \file AudioComponent.hpp
/// \author Lucas T.
/// \brief AudioComponent class declaration

#pragma once

#include <string>

#include "IComponent.hpp"

/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {
    /// \namespace Component
    /// \brief Used for the all component
    namespace Component {

        /// \struct Audio
        /// \brief Transform structure, create the transform components
        struct Audio : public IComponent {

            /// \brief constructor
            Audio() : file(""), active(false) {}

            /// \brief constructor
            Audio(const std::string &_file, bool _active) : file(_file), active(_active) {}
            /*! file name attribute */
            std::string file;
            /*! is the sound active */
            bool active;
        };
    }
}
