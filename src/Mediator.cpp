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

    // _actions[Network::ASK_FOR_HUB] = &Server::Mediator::askHub;
    _actions[Network::ASK_FOR_HUB] = std::bind(&Server::Mediator::askHub, this, std::placeholders::_1, std::placeholders::_2);
    _actions[Network::CLIENT_IS_READY] = std::bind(&Server::Mediator::setPlayerReady, this, std::placeholders::_1, std::placeholders::_2);
    _actions[Network::CLIENT_IS_NOT_READY] = std::bind(&Server::Mediator::setPlayerNotReady, this, std::placeholders::_1, std::placeholders::_2);
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
    
    while (_isRunning) {
        std::cout << "$> ";
        std::getline(std::cin, input);
        if (input == "shutdown" || input == "quit")
            _isRunning = false;
    }
}

void Server::Mediator::createHub(std::string ip)
{
    // Need to initialize a thread
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
    createHub(ip);
    _threads.emplace_back(std::bind(&Server::Hub::start, _hubs.back().get()));
    return _hubs.size();
}

void Server::Mediator::processTcpMessage(Server::TcpConnection *socket)
{
    if (socket->state()) {
        Network::headerTcp *h = static_cast<Network::headerTcp *>((void *)socket->buffer().data());
        if (_actions.find(h->code) != _actions.end()) {
            _actions[h->code](socket, h);
        }
    } else {
        for (auto &i : _hubs) {
            if (i.get()->isInHub(socket->ip()))
                i.get()->removeMember(socket->ip());
        }
    }
}

void Server::Mediator::askHub(Server::TcpConnection *socket, [[maybe_unused]] Network::headerTcp *packet)
{
    Network::headerTcp *toSend = new Network::headerTcp;

    // Assigning code and hub number
    toSend->code = Network::SERVER_CLIENT_IS_IN_HUB;
    toSend->hubNbr = assignHub(socket->ip());

    // Copying the port in the data field
    int data = _hubs.back().get()->port();
    std::memcpy(toSend->data, &data, sizeof(int));

    // Sending the packet to the client
    socket->write(static_cast<void *>(toSend), sizeof(Network::headerTcp));
}

void Server::Mediator::setPlayerReady(Server::TcpConnection *socket, Network::headerTcp *packet)
{
    std::cout <<"setting player ready" << std::endl;
    _hubs[packet->hubNbr].get()->setPlayerReady(socket->ip(), true);
    std::cout << "Player has been set ready" << std::endl;
}

void Server::Mediator::setPlayerNotReady(Server::TcpConnection *socket, Network::headerTcp *packet)
{
    _hubs[packet->hubNbr].get()->setPlayerReady(socket->ip(), false);
}