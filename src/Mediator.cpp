/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** Mediator definition
*/

#include "Mediator.hpp"

Server::Mediator::Mediator() : _tcp(_ioContext)
{
    _boostThread = std::thread(&Server::Mediator::launchBoost, this);
    // start();
}

Server::Mediator::~Mediator()
{
}

void Server::Mediator::launchBoost()
{
    _ioContext.run();
}

void Server::Mediator::start()
{
    _tcp.startAccept();
}

void Server::Mediator::createHub(const std::string &ip)
{
    //need to initialize a thread
    _hubs.emplace_back(Server::Hub(_hubs.size() + 1, ip));
}

// Debug::Logger *l = Debug::Logger::getInstance();
// l->generateDebugMessage(Debug::type::INFO , "Enter the game", "main");
// auto scene = std::shared_ptr<Scenes::IScene>(new Scenes::SplashScene("Splash scene", engine.ECS()));

// engine.SceneMachine()->push(scene);
// engine.SceneMachine()->run();
