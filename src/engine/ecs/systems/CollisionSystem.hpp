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
#include <vector>

#include "ISystem.hpp"
#include "Entity.hpp"
#include "DamageComponent.hpp"
#include "HealthComponent.hpp"
#include "TransformComponent.hpp"
#include "CollisionBox2DComponent.hpp"
/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {
    /// \namespace System
    /// \brief Used for the all System
    namespace System {

        /// \class CollisionSystem
        /// \brief A system that will check collisions between entities
        class CollisionSystem : public ISystem {
            public:
                /// \param entities : entities that needs to be updated
                /// \brief update all entities with the current system
                void update(std::unordered_map<unsigned long long, std::shared_ptr<Entity>> &entities) override;

                /// \param first : an entity
                /// \param second : another entity
                /// \brief checks if both entities have collided
                bool onCollide2D(std::shared_ptr<Entity> &first, std::shared_ptr<Entity> &second);

                /// \param first : an entity
                /// \param second : another entity
                /// \brief checks if both entities have collided and deal damage to one another
                void onCollideDamage2D(std::shared_ptr<Entity> &first, std::shared_ptr<Entity> &second);
        };
    }
}