/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Asteroid object
*/

#pragma once

#include <cmath>
#include <cstdlib>
#include <ctime>

#include "IEnnemy.hpp"
#include "SpeedComponent.hpp"
#include "AudioComponent.hpp"
#include "DamageComponent.hpp"
#include "HealthComponent.hpp"
#include "ScriptComponent.hpp"
#include "SpriteComponent.hpp"
#include "SpawnerComponent.hpp"
#include "TransformComponent.hpp"
#include "Animation2DComponent.hpp"
#include "CollisionBox2DComponent.hpp"
#include "LifeSpanComponent.hpp"

namespace Game {

    /// \class ShipBeam
    /// \brief kinda bullet entity
    class ShipBeam {
		public:
            /// \brief constructor
            /// Initialize Asteroid class
			ShipBeam() = default;

            /// \brief destructor
            /// Destroy Asteroid class
			~ShipBeam() = default;

            /// \brief initialise the entity
            /// \return a pointer to the new entity
            static std::shared_ptr<ECS::Entity> createEntity(std::shared_ptr<ECS::Entity> &parent);
        private:
            /// \brief script for the entity
            /// \return moves the bullet
            static void IA(std::shared_ptr<ECS::Entity> &entity);
    };

    /// \class Ship
    /// \brief ennemy that tries to shot the player
	class Ship : public IEnnemy {
		public:
            /// \brief constructor
            /// Initialize Asteroid class
			Ship() = default;

            /// \brief destructor
            /// Destroy Asteroid class
			~Ship() = default;

            /// \brief initialise the entity
            /// \return a pointer to the new entity
            ECS::Entity *createEntity() override;

            /// \brief creates an entity for a spawner
            /// \return a shared pointer to an entity
            static std::shared_ptr<ECS::Entity> createEntityToSpawn(std::shared_ptr<ECS::Entity> &parent);
        private:
            /// \brief script for the entity
            /// \return moves the ship in a sin wave momement
            static void IA(std::shared_ptr<ECS::Entity> &entity);

            float _startPoint;

            /*! A simple instance of a bullet */
            ShipBeam _weapon;
	};

}

