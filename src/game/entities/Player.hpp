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
    /// \class Player
    /// \brief player class
    class Player
    {
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
        /// \brief script for the entity
        /// \return moves the ship in a sin wave momement
        static void IA(std::shared_ptr<ECS::Entity> &entity);
	};
}

#endif /* !PLEYR_HPP_ */
