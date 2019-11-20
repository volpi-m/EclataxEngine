/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Asteroid object
*/

#include "Asteroid.hpp"

extern "C" Game::IEnnemy *entryPoint()
{
    return new Game::Asteroid;
}

Game::Asteroid::Asteroid()
{
    std::cout << "Rapablung I'm falling into space" << std::endl;
}

// Game::Asteroid::initComponent()
// {
    
// }
