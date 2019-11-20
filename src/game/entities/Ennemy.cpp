/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Ennemy
*/

#include "Ennemy.hpp"

extern "C" Game::IEnnemy *entryPoint()
{
    return new Game::Ennemy;
}

Game::Ennemy::Ennemy()
{
    std::cout << "Here I am to destroy the player" << std::endl;
}

Game::Ennemy::~Ennemy()
{
}
