/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Asteroid object
*/

#pragma once

#include "Entity.hpp"

class Asteroid : public ECS::Entity
{
	public:
		Asteroid(const std::string &tag = "Asteroid");
		~Asteroid();

	private:
};
