/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** CollisionSystem class declaration
*/

/// \file IASystem.hpp
/// \author Lucas T.
/// \brief IASystem class declaration

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

                /// \param entity : entities that needs to be updated
                /// \param func : new script (function pointer)
                /// \brief adds a new script to the entity component
                void setScript(std::shared_ptr<Entity> &entity, void (*func)(std::shared_ptr<ECS::Entity> &entity));
 
                /// \param entity : entities that needs to be updated
                /// \brief deletes the script of an entity
                void deleteScript(std::shared_ptr<Entity> &entity);
        };
    }
}