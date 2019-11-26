/*
** EPITECH PROJECT, 2019
** rType
** File description:
** Hub methods
*/

#include "Hub.hpp"

Server::Hub::Hub(int newId, const std::string &creator, boost::asio::io_context &ioContext) : 
    _udp(ioContext, std::bind(&Server::Hub::processUdpMessage, this, std::placeholders::_1)),
    _id(newId)
{
    Debug::Logger *l = Debug::Logger::getInstance();
    std::string msg("create hub with : ");
    l->generateDebugMessage(Debug::type::INFO , msg + creator, "main");
    addMember(creator);
}

Server::Hub::~Hub()
{
}

bool Server::Hub::addMember(const std::string &newMember)
{
    if (isFull())
        return false;
    else {
        _players.emplace_back(Server::Player(newMember, false));
        return true;
    }
}

bool Server::Hub::isFull()
{
    if (_players.size() >= HUBLIMIT)
        return true;
    else
        return false;
}

void Server::Hub::setPlayerReady(const std::string &ip, bool state)
{
    for (auto &i : _players)
        if (i.ip == ip)
            i.isReady = state;
}

void Server::Hub::sendToAllPlayer(void *msg, const std::size_t size)
{
    for (auto &i : _players) {
        _udp.write(i.ip, msg, size);
    }
}

void Server::Hub::startGame()
{
    Debug::Logger *l = Debug::Logger::getInstance(".log");
    std::string msg("Hub number ");
    l->generateDebugMessage(Debug::type::INFO , "Starting the game", msg + std::to_string(_id));
    auto scene = std::shared_ptr<Scenes::IScene>(new Scenes::SplashScene("Splash scene", _engine.ECS()));

    _engine.SceneMachine()->push(scene);
    while(_engine.SceneMachine()->run() != false) {
        // get everything to be send
        // update event stack
        // send event to scene
    }
}

void Server::Hub::processUdpMessage(Server::UdpNetwork *udp)
{
    std::cout << "treat a message" << std::endl;
    Network::headerUdp *h = static_cast<Network::headerUdp *>((void *)udp->buffer().data());
}
