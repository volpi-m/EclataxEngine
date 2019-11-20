/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** CollisionSystem class declaration
*/

/// \file CollisionSystem.hpp
/// \author Lucas T.
/// \brief CollisionSystem class declaration

#pragma once

#include <unordered_map>
#include <iostream>
#include <memory>

#include "Entity.hpp"
#include "ISystem.hpp"
#include "ScriptComponent.hpp"

/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {
    /// \namespace System
    /// \brief Used for the all System
    namespace System {

        /// \class IASystem
        /// \brief A system that will call an IA for an entity
        class IASystem : public ISystem {
            public:
                /// \param entities : entities that needs to be updated
                /// \brief update all entities with the current system
                void update(std::unordered_map<unsigned long long, std::shared_ptr<Entity>> &entities) override;
        };
    }
}