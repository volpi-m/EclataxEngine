/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Asteroid object
*/

#pragma once

#include <cmath>
#include <random>

#include "Ship.hpp"

namespace Game {

    /// \class Fleet
    /// \brief A battle fleet composed of Ship entities
	class Fleet : public IEnnemy {
		public:
            /// \brief constructor
            /// Initialize Asteroid class
			Fleet() = default;

            /// \brief destructor
            /// Destroy Asteroid class
			~Fleet() = default;

            /// \brief initialise the entity
            /// \return a pointer to the new entity
            ECS::Entity *createEntity() override;
        private:
            /// \brief script for the entity
            /// \return moves the ship in a sin wave momement
            static void IA(std::shared_ptr<ECS::Entity> &entity);
	};
}