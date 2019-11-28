/*
** EPITECH PROJECT, 2019
** rType
** File description:
** Hub methods
*/

#include "Hub.hpp"

Server::Hub::Hub(int newId, const std::string &creator, boost::asio::io_context &ioContext) : 
    _udp(ioContext, std::bind(&Server::Hub::processUdpMessage, this, std::placeholders::_1)),
    _id(newId), _port(_udp.port())
{
    std::cout << "Entering the hub constructor" << std::endl;
    Debug::Logger *l = Debug::Logger::getInstance(".log");
    std::string msg("create hub with : ");
    l->generateDebugMessage(Debug::type::INFO , msg + creator, "hub constructor");
    addMember(creator);
}

Server::Hub::~Hub()
{
}

void Server::Hub::start()
{
    Debug::Logger *l = Debug::Logger::getInstance();
    std::string msg("hub number ");

    l->generateDebugMessage(Debug::type::INFO , msg + std::to_string(_id) + " is running !" , "hub starter");
    std::unique_lock<std::mutex> lock(_mutex);
    while (allIsReady())
        _cond_var.wait(lock);
    l->generateDebugMessage(Debug::type::INFO , "Here we go !!!!" , "hub starter");
    startGame();
}

bool Server::Hub::allIsReady()
{
    for (auto &i : _players) {
        if (i.isReady == false)
            return false;
    }
    return true;
}

bool Server::Hub::addMember(const std::string &ip)
{
    if (isFull())
        return false;
    else {
        _players.emplace_back(Server::Player(ip, false));
        return true;
    }
}

void Server::Hub::removeMember(const std::string &ip)
{
    _players.remove_if([&] (Player &p) { return(p.ip == ip); });
}

bool Server::Hub::isFull()
{
    if (_players.size() >= HUBLIMIT)
        return true;
    else
        return false;
}

bool Server::Hub::isInHub(const std::string &ip)
{
    for (auto &i : _players) {
        if (i.ip == ip)
            return true;
    }
    return false;
}

void Server::Hub::setPlayerReady(const std::string &ip, bool state)
{
    for (auto &i : _players)
        if (i.ip == ip) {
            _cond_var.notify_one();
            i.isReady = state;
        }
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

    // Entity parameters
    std::size_t id = 0;
    float x = 10;
    float z = 10;
    float y = 10;

    while (_engine.SceneMachine()->run() != false) {

        // THE FOLLOWING IS AN EXAMPLE
        struct Network::headerUdp *data = new Network::headerUdp();
        Network::Entity *entity = new Network::Entity;

        // Filling the structure
        entity->id = id;
        entity->x = x += 0.01;
        entity->y = y += 0.01;
        entity->z = z += 0.01;
        std::memcpy(entity->texture, "ressources/r-typesheet1.gif", 27);
        data->code = Network::SERVER_TICK;

        // Sending the packet to all players
        std::memcpy(data->data, (void *)entity, Network::UDP_BUF_SIZE);
        for (auto &it : _players)
            _udp.write(it.ip, (void *)data, sizeof(int) + Network::UDP_BUF_SIZE);

        // Waiting before sending another packet
        // std::this_thread::sleep_for(std::chrono::seconds(1));

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
