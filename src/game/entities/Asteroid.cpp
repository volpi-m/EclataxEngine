/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Asteroid object
*/

#include "Asteroid.hpp"

extern "C" ECS::Entity *entryPoint()
{
    return new Asteroid;
}

Asteroid::Asteroid(const std::string &tag) : Entity(tag)
{
    std::cout << "Rapablung I'm falling into space" << std::endl;
}

Asteroid::~Asteroid()
{
}
