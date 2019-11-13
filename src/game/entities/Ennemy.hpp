/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** ennemy entities
*/

#pragma once

#include "Entity.hpp"

class Ennemy : public ECS::Entity
{
	public:
		Ennemy(const std::string &tag = "Ennemy");
		~Ennemy();

	private:
};
