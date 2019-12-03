/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** MovementSystem class declaration
*/

/// \file LifeManipulatorSystem.hpp
/// \author Lucas T.
/// \brief LifeManipulator class declaration

#pragma once

#include <unordered_map>
#include <iostream>
#include <memory>
#include <vector>

#include "ISystem.hpp"
#include "Entity.hpp"
#include "Logger.hpp"
#include "HealthComponent.hpp"

/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {
    /// \namespace System
    /// \brief Used for the all System
    namespace System {

        /// \class HealthManipulator
        /// \brief A system that will update the Life component
        class HealthManipulator : public ISystem {
            public:
                /// \param entities : entities that needs to be updated
                /// \brief update all entities with the current system
                void update(std::unordered_map<unsigned long long, std::shared_ptr<Entity>> &entities) override;

                /// \param entity : the target entity
                /// \brief substract life of an entity
                void subHealth(std::shared_ptr<Entity> &entity, int health);

                /// \param entity : the target entity
                /// \brief add life to an entity
                void addHealth(std::shared_ptr<Entity> &entity, int health);

                /// \param entity : the target entity
                /// \brief set life of an entity
                void setHealth(std::shared_ptr<Entity> &entity, int health);

                /// \param entity : the target entity
                /// \brief set life limit of an entity
                void setHealthLimit(std::shared_ptr<Entity> &entity, int health);

                /// \return the health of the current entity
                /// \param entity : the target entity
                /// \brief get the healh of the tageted entity
                int health(std::shared_ptr<Entity> &entity) const;

                /// \return the health limit of the current entity
                /// \param entity : the target entity
                /// \brief get the healh limit of the tageted entity
                int healthLimit(std::shared_ptr<Entity> &entity) const;
        };
    }
}