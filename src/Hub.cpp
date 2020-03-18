/*
** EPITECH PROJECT, 2019
** rType
** File description:
** Hub methods
*/

#include "Hub.hpp"

Server::Hub::Hub(int newId, const std::string &creator, boost::asio::io_context &ioContext, const std::string &startingScene)
    : _stoped        { false                                                                              }
    , _isPlaying     { false                                                                              }
    , _udp           { ioContext, std::bind(&Server::Hub::processUdpMessage, this, std::placeholders::_1) }
    , _id            { newId                                                                              }
    , _port          { _udp.port()                                                                        }
    , _startingScene { _startingScene                                                                     }
{
    _actions[Network::CLIENT_TICK] = std::bind(&Server::Hub::addEvent, this, std::placeholders::_1, std::placeholders::_2);
    _actions[Network::CLIENT_ERROR] = std::bind(&Server::Hub::playerError, this, std::placeholders::_1, std::placeholders::_2);
    addMember(creator);
}

void Server::Hub::start()
{
    // TODO
    // Creating the entry point for scenes. To be replaced with rtype.conf content.
    std::shared_ptr<Scenes::IScene> lib(_engine.LibLoader()->openLibrary<Scenes::IScene>("lib/libmainscene.so"));

    if (!lib.get())
    {
        Debug::Logger::printDebug(Debug::FATAL, "Couldn't load main scene", "Server::Hub::start()");
        return;
    }

    // Pushing the scene to the scene machine.
    std::shared_ptr<Scenes::IScene> scene(lib);
    _engine.SceneStateMachine()->push(scene);

    // Initialise available players
    initStatePlayers();

    while (!_stoped && !_players.empty())
    {
        // Running the current scene behaviour
        _engine.SceneStateMachine()->update();
    }
}


// void Server::Hub::start()
// {
//     Debug::Logger::printDebug(Debug::type::INFO , "hub number " + std::to_string(_id) + " is running !" , "Server::Hub::start()");

//     auto scene = std::shared_ptr<Scenes::IScene>(new Scenes::HubLoadingScene("Hub scene", _engine.ECS(), _players.size()));
//     _engine.SceneMachine()->push(scene);

//     initStatePlayers();
//     while (!_stoped) {

//         _engine.SceneMachine()->run();
//         std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
//         std::stack<Network::Entity> &entities = _engine.SceneMachine()->getCurrentSceneEntityStack();
//         while (!entities.empty()) {
//             sendEntity(entities.top());
//             entities.pop();
//         }
//         {
//             handleEvent();
//             std::lock_guard<std::mutex> lock(_mutex);

//             // // send event to scene
//             _engine.SceneMachine()->sendEventsToCurrentScene(_event);
//         }

//         std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
//         std::this_thread::sleep_for(std::chrono::milliseconds(16 - std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()));
//         if (allIsReady()) {
//             _engine.SceneMachine()->remove();
//             std::stack<Network::Entity> &entities = _engine.SceneMachine()->getCurrentSceneEntityStack();
//             while (!entities.empty()) {
//                 sendEntity(entities.top());
//                 entities.pop();
//             }
//             startGame();
//             _engine.SceneMachine()->clear();
//             auto newHub = std::shared_ptr<Scenes::IScene>(new Scenes::HubLoadingScene("Hub scene", _engine.ECS(), _players.size()));
//             _engine.SceneMachine()->push(newHub);
//         }
//     }
// }

void Server::Hub::stop()
{
    std::lock_guard<std::mutex> lock(_mutex);
    Network::headerUdp data;
    char msg[20] = "Server was stopped";

    _stoped = true;
    data.code = Network::CLIENT_ERROR;

    std::memcpy(data.data, &msg, sizeof(msg));
    sendToAllPlayer(&data, sizeof(data));
    _players.clear();
}

void Server::Hub::startGame()
{
    _isPlaying = true;
    // Scenes::IScene *newScene = nullptr;
 
    // auto scene = std::shared_ptr<Scenes::IScene>(new Scenes::Level1Scene("level1Scene", _engine.ECS(), _players.size()));

    // _engine.SceneMachine()->push(scene);

    // while (!_players.empty() && !_stoped) {
    //     newScene = _engine.SceneMachine()->run();
    //     // Calculatin time of execution
    //     std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    //     // send entites
    //     std::stack<Network::Entity> &entities = _engine.SceneMachine()->getCurrentSceneEntityStack();
    //     while (!entities.empty()) {
    //         sendEntity(entities.top());
    //         entities.pop();
    //     }

    //     if (_engine.SceneMachine()->isToPop() && !newScene) {
    //         if (_engine.SceneMachine()->name() == "Hub scene" && _engine.SceneMachine()->isToSwap())
    //             _engine.SceneMachine()->pop("Hub scene");
    //         else
    //             _engine.SceneMachine()->pop();
    //         break;
    //     } else if (newScene) {
    //         std::shared_ptr<Scenes::IScene> s(newScene);
    //         _engine.SceneMachine()->push(s);
    //     }
    //     {
    //         std::lock_guard<std::mutex> lock(_mutex);
    //        // send event to scene
    //         _engine.SceneMachine()->sendEventsToCurrentScene(_event);

    //         // update event stack
    //         while (!_event.empty())
    //             _event.pop();
    //     }

    //      // Sleeping before starting the next frame
    //     std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    //     std::this_thread::sleep_for(std::chrono::milliseconds(16 - std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()));
    // }
    // _isPlaying = false;
    // initStatePlayers();
}

bool Server::Hub::allIsReady()
{
    for (auto &i : _players)
        if (i.isReady == false)
            return false;
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

bool Server::Hub::removeMember(const std::string &ip)
{
    bool rm = false;
    std::unique_lock<std::mutex> lock(_mutex);

    for (unsigned int i = 0; i < _players.size(); i++)
        if (_players[i].ip == ip) {
            _players.erase(_players.begin() + i);
            rm = true;
        }
    return (rm);
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
    for (auto &player : _players)
        if (player.ip == ip)

            return true;
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
    for (auto &player : _players)
        _udp.write(player.ip, msg, size);
}


void Server::Hub::processUdpMessage(Server::UdpNetwork *socket)
{
    Network::headerUdp *h = static_cast<Network::headerUdp *>((void *)socket->buffer().data());
    _actions[h->code](socket, h);
}

void Server::Hub::addEvent(Server::UdpNetwork *socket, Network::headerUdp *packet)
{
    // need to find the position of socket->remoteIp()

    std::lock_guard<std::mutex> lock(_mutex);

    int nb = -1;
    for (unsigned int i = 0; i != _players.size(); i++)
        if (_players[i].ip == socket->remoteIp())
            nb = i;
    if (nb != -1) {
        size_t event;
        std::memcpy(&event, packet->data, sizeof(size_t));
        _event.emplace(nb + 1, event);
    }
}

void Server::Hub::playerError(Server::UdpNetwork *socket, Network::headerUdp *packet)
{
    std::string ip = socket->remoteIp();

    removeMember(ip);
}

void Server::Hub::sendEntity(Network::Entity &e)
{
    Network::headerUdp data = Network::headerUdp();

    data.code = Network::SERVER_TICK;
    std::memcpy(&data.data, &e, Network::UDP_BUF_SIZE);
    sendToAllPlayer(&data, sizeof(data));
}

void Server::Hub::initStatePlayers()
{
    std::unique_lock<std::mutex> lock(_mutex);

    for (auto &i : _players)
        i.isReady = false;
}

void Server::Hub::handleEvent()
{
    // if (_event.size()) {
    //     if (_event.size() == 1 && _event.front().second & Scenes::SPACE) {
    //             _players[_event.front().first - 1].isReady = true;
    //     } else {
    //         auto current = _event.front();

    //         for (auto last = _event.back(); current != last; current = _event.front()) {
    //             if (current.second & Scenes::SPACE) {
    //                 _players[current.first - 1].isReady = true;
    //             }
    //             _event.push(current);
    //             _event.pop();
    //         }
    //     }






        // if ((i.second & 32) == 32)
        //     _players[i.first - 1].isReady = true;
        // for (auto last = _event.back(); i != last; i = _event.front()) {
        //     if ((i.second & 32) == 32) {
        //         _players[i.first - 1].isReady = true;
        //     }
        //     _event.push(_event.front());
        //     _event.pop();
        // }
    // }
}