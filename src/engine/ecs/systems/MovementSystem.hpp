/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** MovementSystem class declaration
*/

/// \file MovementSystem.hpp
/// \author Lucas T.
/// \brief MovementSystem class declaration

#pragma once

#include <unordered_map>
#include <iostream>
#include <memory>
#include <vector>

#include "ISystem.hpp"
#include "Entity.hpp"
#include "TransformComponent.hpp"

/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {
    /// \namespace System
    /// \brief Used for the all System
    namespace System {

        /// \class MovementSystem
        /// \brief A system that will update the Transform component
        class MovementSystem : public ISystem {
            public:
                /// \param entities : entities that needs to be updated
                /// \brief update all entities with the current system
                void update(std::unordered_map<unsigned long long, std::shared_ptr<Entity>> &entities) override;
        };
    }
}