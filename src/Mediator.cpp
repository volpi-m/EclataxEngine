/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** Mediator definition
*/

#include "Mediator.hpp"

rType::Mediator::Mediator()
{
    start();
}

rType::Mediator::~Mediator()
{
}

void rType::Mediator::start()
{
    Debug::Logger *l = Debug::Logger::getInstance();
    l->generateDebugMessage(Debug::type::INFO , "Enter the game", "main");
    Scenes::SplashScene("TOTO");
    // auto scene = std::shared_ptr<Scenes::IScene>(new Scenes::SplashScene("Splash scene", engine.ECS()));

    // engine.SceneMachine()->push(scene);
    // engine.SceneMachine()->run();
}
