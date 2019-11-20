/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Asteroid object
*/

#pragma once

#include "IEnnemy.hpp"

/// \namespace Game
/// \brief Used for the game part classes
namespace Game {

    /// \class Asteroid
    /// \brief ennemy that falling on the player
	class Asteroid : public IEnnemy
	{
		public:
            /// \brief constructor
            /// Initialize Asteroid class
			Asteroid();
            /// \brief destructor
            /// Destroy Asteroid class
			~Asteroid() = default;

            /// \brief initialise the component in game engine
            void initComponent() override;

            // virtual void move() = 0;
            // virtual void shot() = 0;
            // virtual void kill() = 0;

		private:
	};
}