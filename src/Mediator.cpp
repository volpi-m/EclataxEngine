/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** Mediator definition
*/

#include "Mediator.hpp"

Server::Mediator::Mediator() : _tcp (_ioContext, 
    std::function<void(Server::TcpConnection *)>(std::bind(&Server::Mediator::processTcpMessage, this, std::placeholders::_1))), 
    _isRunning(true)
{
    Debug::Logger *l = Debug::Logger::getInstance();
    l->generateDebugMessage(Debug::type::INFO , "Create Mediator", "Mediator ctor");
    _boostThread = std::thread(&Server::Mediator::launchBoost, this);
}

Server::Mediator::~Mediator()
{
    _ioContext.stop();
    _boostThread.join();
}

void Server::Mediator::launchBoost()
{
    _ioContext.run();
}

void Server::Mediator::start()
{
    std::string input;
    while(_isRunning) {
        std::cout << "$>";
        std::getline(std::cin, input);
        if (input == "shutdown")
            _isRunning = false;
    }
}

void Server::Mediator::createHub(std::string ip)
{
    //need to initialize a thread
    _mut.lock();
    _hubs.emplace_back(std::make_unique<Server::Hub>(_hubs.size() + 1, ip, _ioContext));
    _mut.unlock();
}

int Server::Mediator::hubNumber()
{
    return _hubs.size();
}

int Server::Mediator::assignHub(std::string ip)
{
    for (auto &i : _hubs) {
        if (!(*i).isFull()) {
            (*i).addMember(ip);
            return ((*i).id());
        }
    }
    _threads.emplace_back(&Server::Mediator::createHub, this, ip);
    return _hubs.size();
}

void Server::Mediator::processTcpMessage(Server::TcpConnection *socket)
{
    Debug::Logger *l = Debug::Logger::getInstance();
    l->generateDebugMessage(Debug::type::INFO , "Enter the callback function !", "Mediator");
    Server::headerTcp *h = static_cast<Server::headerTcp *>((void *)socket->buffer().data());
    std::cout << "Message from : " << socket->ip() << std::endl;
    if (h->code == ASK_FOR_HUB) {
        Server::headerTcp h;
        h.code = SERVER_CLIENT_IS_IN_HUB;
        int n = assignHub(socket->ip());
        h.data = (void *)&n;
        socket->write(static_cast<void *>(&h), sizeof(h));
    }
}