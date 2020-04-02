/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Pleyr
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

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

namespace Game
{
    /// \class PlayerShipBeam
    /// \brief kinda bullet entity
    class PlayerShipBeam {
	public:
        /// \brief constructor
        /// Initialize Asteroid class
		PlayerShipBeam() = default;
        
        /// \brief destructor
        /// Destroy Asteroid class
		~PlayerShipBeam() = default;
        
        /// \brief initialise the entity
        /// \return a pointer to the new entity
        static std::shared_ptr<ECS::Entity> createEntity(std::shared_ptr<ECS::Entity> &parent);
    private:
        
        /// \brief script for the entity
        /// \param entity : entity to move
        static void IA(std::shared_ptr<ECS::Entity> &entity);
    };

    /// \class Player
    /// \brief player class
    class Player {
    public:
        /// \brief constructor
        /// Initialize Asteroid class
        Player() = default;

        /// \brief destructor
        /// Destroy Asteroid class
        ~Player() = default;

        /// \brief initialise the entity
        /// \return a pointer to the new entity
        ECS::Entity *createEntity();
    private:

        /// \brief Reset the pos of the player
        /// \param entty : player
        static void IA(std::shared_ptr<ECS::Entity> &entity);
	};
}

#endif /* !PLEYR_HPP_ */
