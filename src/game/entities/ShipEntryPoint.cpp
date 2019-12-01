/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Asteroid object
*/

#include "Ship.hpp"

extern "C" ECS::Entity *entryPoint()
{
    Game::Ship ship;

    return ship.createEntity();
}