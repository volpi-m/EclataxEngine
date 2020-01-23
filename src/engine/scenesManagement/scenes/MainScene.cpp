//
// EPITECH PROJECT, 2019
// MainScene.cpp
// File description:
// dumy scene
//

/// \file MainScene.cpp
/// \author Lucas T.
/// \brief MainScene class methods

#include "MainScene.hpp"

extern "C" Scenes::IScene *entryPoint()
{
    return new Scenes::MainScene;
}

Scenes::MainScene::MainScene(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS, std::shared_ptr<Module::IMediator> &mediator) : AScene(name, ECS, mediator) {}

void Scenes::MainScene::update(float deltaTime) 
{
	(void) deltaTime;
	Debug::Logger::printDebug(Debug::INFO, "The MainScene is being updated, poping the scene.", "MainScene::update()");

	// calling the mediator for the sake of the example.
	_mediator->notify(this, Module::POP, nullptr);
}

void Scenes::MainScene::onCreate() 
{
	Debug::Logger::printDebug(Debug::INFO, "onCreate method called.", "MainScene::onCreate()");
}

void Scenes::MainScene::onDestroy() 
{
	Debug::Logger::printDebug(Debug::INFO, "onDestroy method called.", "MainScene::onDestroy()");
}

void Scenes::MainScene::onActivate() 
{
	Debug::Logger::printDebug(Debug::INFO, "onActivate method called.", "MainScene::onActivate()");
}

void Scenes::MainScene::onDeactivate() 
{
	Debug::Logger::printDebug(Debug::INFO, "onDeactivate method called.", "MainScene::onDeactivate()");
}
