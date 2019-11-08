/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Game Engine methods
*/

#include "GameEngine.hpp"

Game::GameEngine::GameEngine() {}

Game::GameEngine::~GameEngine() {}

bool Game::GameEngine::isInitialised() const
{
    return _initialised;
}

Module::EntityComponentSystem &Game::GameEngine::ECS()
{
    return _ecs;
};

Module::SceneMachine &Game::GameEngine::SceneManager()
{
    return _sceneMachine;
};
