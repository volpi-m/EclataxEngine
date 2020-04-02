/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** BeeEntrypoint
*/

#include "Bee.hpp"

extern "C" ECS::Entity *entryPoint()
{
    Game::Bee bee;

    return bee.createEntity();
}
