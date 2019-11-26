/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component Spawner
*/

/// \file Spawner.hpp
/// \author Someone
/// \brief SpawnerComponent class declaration

#pragma once

#include "Entity.hpp"

#include <chrono>

#include "IComponent.hpp"

/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {
    /// \namespace Component
    /// \brief Used for the all component
    namespace Component {

        /// \struct Spawner
        /// \brief Spawner structure, create the Spawner component
        struct Spawner : public IComponent {
            
            /// \brief constructor
            Spawner() : seconds(5), createBlueprint(nullptr), timeSinceLastSpawn(std::chrono::high_resolution_clock::now()) {}

            /// \brief constructor
            /// \param _seconds : time between each spawns
            /// \param _createBlueprint : entity template that will be used
            Spawner(std::chrono::seconds _seconds, std::shared_ptr<Entity> (*_createBlueprint)(std::shared_ptr<Entity> &parent)) : seconds(_seconds), createBlueprint(_createBlueprint), timeSinceLastSpawn(std::chrono::high_resolution_clock::now()) {}

            /*! time between spawns attribute */
            std::chrono::seconds seconds;
            /*! entity that will be spawned */
            std::shared_ptr<Entity> (*createBlueprint)(std::shared_ptr<Entity> &parent);
            /*! time between spawns attribute */
            std::chrono::high_resolution_clock::time_point timeSinceLastSpawn;
        };
    }
}
