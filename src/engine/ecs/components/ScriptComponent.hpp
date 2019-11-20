/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component Script
*/

/// \file ScriptComponent.hpp
/// \author Lucas T.
/// \brief Script class declaration

#pragma once

#include "Entity.hpp"

/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {
    /// \namespace Component
    /// \brief Used for the all component
    namespace Component {

        /// \struct Script
        /// \brief Script structure, create the Script components
        struct Script : public IComponent {
            
            /// \brief constructor
            Script() : updateScript(nullptr) {}

            /// \brief constructor
            Script(void (*newScript)(std::shared_ptr<Entity> &entity)) : updateScript(newScript) {}

            /*! pointer to function attribute */
            void (*updateScript)(std::shared_ptr<Entity> &entity);
        };
    }
}
