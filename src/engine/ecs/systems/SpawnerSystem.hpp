/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** SpawnerSystem class declaration
*/

/// \file SpawnerSystem.hpp
/// \author Lucas T.
/// \brief SpawnerSystem class declaration

#pragma once

#include <unordered_map>
#include <iostream>
#include <memory>

#include "ECS.hpp"
#include "Entity.hpp"
#include "ISystem.hpp"
#include "SpawnerComponent.hpp"

/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {

    /// \namespace System
    /// \brief Used for the all System
    namespace System {

        /// \class SpawnerSystem
        /// \brief A system that will spawns entities
        class SpawnerSystem : public ISystem {
            public:
                /// \param entities : entities that needs to be updated
                /// \brief update all entities with the current system
                void update(std::unordered_map<unsigned long long, std::shared_ptr<Entity>> &entities) override;

                /// \brief spawn e new entity
                /// \param entity : entity with the spawn component
                /// \param ECS : the ecs to store the new child
                void spawn(std::shared_ptr<Entity> &entity, std::shared_ptr<Module::EntityComponentSystem> &ECS);
        };
    }
}