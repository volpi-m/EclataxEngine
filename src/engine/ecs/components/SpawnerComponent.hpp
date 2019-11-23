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
            Spawner() : seconds(5), blueprint(new Entity("blueprint")) {}

            /// \brief constructor
            /// \param _seconds : time between each spawns
            /// \param _entity : entity template that will be used
            Spawner(std::chrono::seconds _seconds, std::shared_ptr<Entity> &_entity) : seconds(_seconds), blueprint(_entity) {}

            /*! time between spawns attribute */
            std::chrono::seconds seconds;
            /*! entity that will be spawnable attribute */
            std::shared_ptr<Entity> blueprint;
        };
    }
}
