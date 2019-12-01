/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Entity class declaration
*/

#pragma once

#include <unordered_map>
#include <iostream>
#include <memory>
#include <vector>

#include "IComponent.hpp"
#include "Entity.hpp"

/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {

    /// \namespace System
    /// \brief Used for all the System subclasses
    namespace System {

        /// \namespace Flags
        /// \brief Flags for systems
        namespace Flags {
        typedef enum e_flags {Movement, AudioPlayer, LifeManipulator, Gravity, Animation, Script, Parallax, IA, Spawner, LifeSpan, Collision, HealthManipulator, RenderSystem} flags;
        }
    }
    /// \class ISystem
    /// \brief A interface for all the systems
    class ISystem {
        public:
            /// \param entities : entities that needs to be updated
            /// \brief update all entities with the current system with the normal behavior of the system
            virtual void update(std::unordered_map<unsigned long long, std::shared_ptr<Entity>> &entities) = 0;
    };
}