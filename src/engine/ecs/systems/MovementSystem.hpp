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
#include "SpeedComponent.hpp"

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

                /// \param entity : entity that we want the transform from
                /// \brief get the tranform of the entity
                std::tuple<float, float, float> transform(const std::shared_ptr<Entity> &entity) const;

                /// \param entity : entity that will be updated
                /// \param x : x coordinates
                /// \param y : y coordinates
                /// \param z : z coordinates
                /// \brief update the entity by providing new coordinates
                void setTransform(std::shared_ptr<Entity> &entity, float x, float y, float z);

                /// \param entity : entity that we want to move
                /// \param x : x coordinates
                /// \param y : y coordinates
                /// \param z : z coordinates
                /// \brief move an entity
                void move(std::shared_ptr<Entity> &entity, float x, float y, float z);

                /// \param entity : entity that we want the speed from
                /// \brief get the speed of a entity
                float speed(const std::shared_ptr<Entity> &entity);
        };
    }
}