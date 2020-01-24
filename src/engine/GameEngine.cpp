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

Game::GameEngine::GameEngine() : _ecs(new Module::EntityComponentSystem), _libraryLoader(new Utils::LibraryLoader), _sceneStateMachine(new Module::SceneStateMachine(_ecs)), _initialised(true) {}

Game::GameEngine::~GameEngine() {}

bool Game::GameEngine::isInitialised() const
{
    return _initialised;
}

std::shared_ptr<Module::EntityComponentSystem> &Game::GameEngine::ECS()
{
    return _ecs;
};

std::shared_ptr<Utils::LibraryLoader> &Game::GameEngine::LibLoader()
{
    return _libraryLoader;
};


std::shared_ptr<Module::SceneStateMachine> &Game::GameEngine::SceneStateMachine()
{
    return _sceneStateMachine;
};
