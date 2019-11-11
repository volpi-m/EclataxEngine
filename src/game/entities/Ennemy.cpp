/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Ennemy
*/

#include "Ennemy.hpp"

extern "C" ECS::Entity *entryPoint()
{
    return new Ennemy;
}

Ennemy::Ennemy(const std::string &tag) : Entity(tag)
{
    std::cout << "Here I am to destroy the player" << std::endl;
}

Ennemy::~Ennemy()
{
}
