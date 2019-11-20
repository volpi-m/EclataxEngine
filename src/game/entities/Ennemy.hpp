/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** ennemy entities
*/

#pragma once

#include <string>

#include "IEnnemy.hpp"

/// \namespace Game
/// \brief Used for the game part classes
namespace Game {

	class Ennemy : public Game::IEnnemy
	{
		public:
			Ennemy();
			~Ennemy();

            void initComponent();
		private:
	};
}