/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Asteroid object
*/

#pragma once

#include "IEnnemy.hpp"
#include "SpeedComponent.hpp"
#include "AudioComponent.hpp"
#include "DamageComponent.hpp"
#include "HealthComponent.hpp"
#include "ScriptComponent.hpp"
#include "SpriteComponent.hpp"
#include "TransformComponent.hpp"
#include "ParticulesComponent.hpp"
#include "AccelerationComponent.hpp"
#include "CollisionBox2DComponent.hpp"

namespace Game {

    /// \class Asteroid
    /// \brief ennemy that falling on the player
	class Asteroid : public IEnnemy {
		public:
            /// \brief constructor
            /// Initialize Asteroid class
			Asteroid() = default;

            /// \brief destructor
            /// Destroy Asteroid class
			~Asteroid() = default;

            /// \brief initialise the entity
            /// \return a pointer to the new entity
            ECS::Entity *createEntity() override;
        private:
            static void IA(std::shared_ptr<ECS::Entity> &entity);
	};
}