/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component Text
*/

/// \file TextComponent.hpp
/// \author Lucas T.
/// \brief TextComponent class declaration

#pragma once

#include <string>

#include "IComponent.hpp"

/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {
    /// \namespace Component
    /// \brief Used for the all component
    namespace Component {

        /// \struct Text
        /// \brief Text structure, create the Text component
        struct Text : public IComponent {
            
            /// \brief constructor
            Text() : text("") {}

            /// \brief constructor
            /// \param string : text value 
            Text(const std::string &string) : text(string) {}

            /*! text attribute */
            std::string text;
            /*! font of the text */
            std::string font;
        };
    }
}
