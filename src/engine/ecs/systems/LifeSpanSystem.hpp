/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** LifeSpanSystem class declaration
*/

/// \file LifeSpanSystem.hpp
/// \author Lucas T.
/// \brief LifeSpanSystem class declaration

#pragma once

#include <unordered_map>
#include <iostream>
#include <memory>

#include "Entity.hpp"
#include "ISystem.hpp"
#include "LifeSpanComponent.hpp"

/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {

    /// \namespace System
    /// \brief Used for the all System
    namespace System {

        /// \class LifeSpanSystem
        /// \brief A system that will despawn entities
        class LifeSpanSystem : public ISystem {
            public:
                /// \param entities : entities that needs to be updated
                /// \brief update all entities with the current system
                void update(std::unordered_map<unsigned long long, std::shared_ptr<Entity>> &entities) override;
        };
    }
}