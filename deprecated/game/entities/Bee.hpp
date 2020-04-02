/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Bees
*/

#ifndef BEE_HPP_
#define BEE_HPP_

#include <cmath>
#include <random>

#include "IEnnemy.hpp"
#include "SpeedComponent.hpp"
#include "AudioComponent.hpp"
#include "DamageComponent.hpp"
#include "HealthComponent.hpp"
#include "ScriptComponent.hpp"
#include "SpriteComponent.hpp"
#include "TransformComponent.hpp"
#include "Animation2DComponent.hpp"
#include "CollisionBox2DComponent.hpp"
#include "LifeSpanComponent.hpp"

namespace Game
{
    /// \class Bee
    /// \brief another Enemy
    class Bee : public IEnnemy
    {
    public:
        /// \brief constructor
        /// Initialize Bee class
        Bee() = default;

        /// \brief Destructor
        /// Destroy Bee class
        ~Bee() = default;

        /// \brief initialise the entity
        /// \return a pointer to the new entity
        ECS::Entity *createEntity() override;

        /// \brief creates an entity for a spawner
        /// \return a shared pointer to an entity
        static std::shared_ptr<ECS::Entity> createEntityToSpawn(std::shared_ptr<ECS::Entity> &parent);

    private:
        /// \brief script for the entity
        /// \return moves the bee forward
        static void IA(std::shared_ptr<ECS::Entity> &entity);
    };
}

#endif /* !BEES_HPP_ */
