/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Game Engine methods
*/

/// \file GameEngine.cpp
/// \author Lucas T.
/// \brief GameEngine class methods

#include "GameEngine.hpp"

Game::GameEngine::GameEngine() : _ecs(new Module::EntityComponentSystem), _sceneMachine(new Module::SceneMachine), _initialised(true) {}

Game::GameEngine::~GameEngine() {}

bool Game::GameEngine::isInitialised() const
{
    return _initialised;
}

std::shared_ptr<Module::EntityComponentSystem> &Game::GameEngine::ECS()
{
    return _ecs;
};

std::shared_ptr<Module::SceneMachine> &Game::GameEngine::SceneMachine()
{
    return _sceneMachine;
};
