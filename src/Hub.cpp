/*
** EPITECH PROJECT, 2019
** rType
** File description:
** Hub methods
*/

#include "Hub.hpp"

Server::Hub::Hub(int newId, const std::string &creator, boost::asio::io_context &ioContext) : _stoped(false), _isPlaying(false),
    _udp(ioContext, std::bind(&Server::Hub::processUdpMessage, this, std::placeholders::_1)),
    _id(newId), _port(_udp.port())
{
    _actions[Network::CLIENT_TICK] = std::bind(&Server::Hub::addEvent, this, std::placeholders::_1, std::placeholders::_2);
    _actions[Network::CLIENT_ERROR] = std::bind(&Server::Hub::playerError, this, std::placeholders::_1, std::placeholders::_2);
    std::string msg("create hub with : ");
    Debug::Logger *l = Debug::Logger::getInstance(".log");
    l->generateDebugMessage(Debug::type::INFO , msg + creator, "hub constructor");
    addMember(creator);
}

Server::Hub::~Hub()
{
}

void Server::Hub::start()
{
    Debug::Logger *l = Debug::Logger::getInstance(".log");
    std::string msg("hub number ");

    l->generateDebugMessage(Debug::type::INFO , msg + std::to_string(_id) + " is running !" , "Server::Hub::start()");
    std::unique_lock<std::mutex> lock(_mutex);
    while (!allIsReady() && !_stoped) {
        _cond_var.wait(lock);
    }
    lock.unlock();
    if (!_players.empty())
        startGame();
}

void Server::Hub::stop()
{
    _stoped = true;
    _cond_var.notify_one();
    Network::headerUdp data;
    data.code = Network::CLIENT_ERROR;
    char msg[20] = "Server was stopped";
    std::memcpy(data.data, &msg, sizeof(msg));
    sendToAllPlayer(&data, sizeof(data));
    std::unique_lock<std::mutex> lock(_mutex);
    _players.clear();
}

bool Server::Hub::allIsReady()
{
    for (auto &i : _players) {
        if (i.isReady == false)
            return false;
    }
    if (_players.size() != 0)
        return true;
    else
        return false;
}

bool Server::Hub::addMember(const std::string &ip)
{
    if (isOpen()) {
        std::unique_lock<std::mutex> lock(_mutex);
        _players.emplace_back(Server::Player(ip, false));
        return true;
    } else
        return false;
}

void Server::Hub::removeMember(const std::string &ip)
{
    std::unique_lock<std::mutex> lock(_mutex);
    for (unsigned int i = 0; i < _players.size(); i++) {
        if (_players[i].ip == ip)
            _players.erase(_players.begin() + i);
    }
    _cond_var.notify_one();
    // _players.remove_if([&] (Player &p) { return(p.ip == ip); });
}

bool Server::Hub::isOpen()
{
    std::unique_lock<std::mutex> lock(_mutex);
    if (_players.size() >= HUBLIMIT || _isPlaying)
        return false;
    else
        return true;
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
    for (auto &i : _players)
        _udp.write(i.ip, msg, size);
}

void Server::Hub::startGame()
{
    _isPlaying = true;
    Debug::Logger *l = Debug::Logger::getInstance(".log");
    std::string msg("Hub number ");
    l->generateDebugMessage(Debug::type::INFO , "Starting the game", msg + std::to_string(_id));
    auto scene = std::shared_ptr<Scenes::IScene>(new Scenes::SplashScene("Splash scene", _engine.ECS()));

    _engine.SceneMachine()->push(scene);

    while (_engine.SceneMachine()->run() != false && !_players.empty()) {

        // Calculatin time of execution
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

        // send entites
        std::stack<Network::Entity> &entities = _engine.SceneMachine()->getCurrentSceneEntityStack();
        while (!entities.empty()) {
            std::cout << "sending entity n°" << entities.top().id << std::endl; 
            sendEntity(entities.top());
            entities.pop();
        }
        std::cout << "OUT" << std::endl;
        // send event to scene
        _engine.SceneMachine()->sendEventsToCurrentScene(_event);

        // update event stack
        while(!_event.empty())
            _event.pop();

        // Sleeping before starting the next frame
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds(16 - std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()));
    }
    _isPlaying = false;
    l->generateDebugMessage(Debug::type::INFO , "Ending the game", msg + std::to_string(_id));
}

void Server::Hub::processUdpMessage(Server::UdpNetwork *socket)
{
    Network::headerUdp *h = static_cast<Network::headerUdp *>((void *)socket->buffer().data());
    _actions[h->code](socket, h);
}

void Server::Hub::addEvent(Server::UdpNetwork *socket, Network::headerUdp *packet)
{
    // need to find the position of socket->remoteIp()
    int nb = -1;
    for (unsigned int i = 0; i != _players.size(); i++) {
        if (_players[i].ip == socket->remoteIp()) {
            nb = i;
        }
    }
    if (nb != -1) {
        size_t event;
        std::memcpy(&event, packet->data, sizeof(size_t));
        _event.emplace(nb + 1, event);
    }
}

void Server::Hub::playerError(Server::UdpNetwork *socket, Network::headerUdp *packet)
{
    std::string ip = socket->remoteIp();
    Debug::Logger *l = Debug::Logger::getInstance(".log");
    l->generateDebugMessage(Debug::type::ERROR , "Error with the player" + ip + "\nError detail: " + packet->data, "Server::Hub::playerError");
    removeMember(ip);
}

void Server::Hub::sendEntity(Network::Entity &e)
{
    Network::headerUdp data = Network::headerUdp();
    data.code = Network::SERVER_TICK;
    std::memcpy(&data.data, &e, Network::UDP_BUF_SIZE);
    sendToAllPlayer(&data, sizeof(data));
}
