/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** Mediator definition
*/

#include "Mediator.hpp"

Server::Mediator::Mediator() : _reader(CONF_FILE_PATH), _tcp (_ioContext, 
    std::function<void(Server::TcpConnection *)>(std::bind(&Server::Mediator::processTcpMessage, this, std::placeholders::_1))), 
    _isRunning(true)
{
    _boostThread = std::thread(&Server::Mediator::launchBoost, this);
    readEventFile();
    _actions[Network::ASK_FOR_HUB] = std::bind(&Server::Mediator::askHub, this, std::placeholders::_1, std::placeholders::_2);
    _actions[Network::CLIENT_IS_READY] = std::bind(&Server::Mediator::setPlayerReady, this, std::placeholders::_1, std::placeholders::_2);
    _actions[Network::CLIENT_IS_NOT_READY] = std::bind(&Server::Mediator::setPlayerNotReady, this, std::placeholders::_1, std::placeholders::_2);
    _actions[Network::CLIENT_REQUIRE_KEY] = std::bind(&Server::Mediator::sendEvent, this, std::placeholders::_1, std::placeholders::_2);
    _actions[Network::CLIENT_REQUEST_SPRITE] = std::bind(&Server::Mediator::sendSprite, this, std::placeholders::_1, std::placeholders::_2);

    _commands.emplace("exit", std::bind(&Mediator::exit, this, std::placeholders::_1));
    _commands.emplace("hubs", std::bind(&Mediator::hubs, this, std::placeholders::_1));
    _commands.emplace("kick", std::bind(&Mediator::kick, this, std::placeholders::_1));
    _commands.emplace("help", std::bind(&Mediator::help, this, std::placeholders::_1));
}

Server::Mediator::~Mediator()
{
    _ioContext.stop();
    _boostThread.join();
    for (auto &i : _hubs) {
        i.get()->stop();
    }
    for (auto &i : _threads) {
        i.join();
    }
}

void Server::Mediator::launchBoost()
{
    _ioContext.run();
}

void Server::Mediator::readEventFile()
{
    int value = 1;
    auto i = _reader.conf(std::to_string(value));
    for (auto i = _reader.conf(std::to_string(value)); i.has_value(); i = _reader.conf(std::to_string(value))) {
        _eventTemplate[value] = i.value();
        value <<= 1;
    }
}

void Server::Mediator::start()
{
    std::string input("input");
    while (_isRunning)
    {
        // Displaying the prompt and getting the input from the user.
        std::cout << "$> ";
        std::getline(std::cin, input);

        // Needs better string formating.
        if (_commands.find(input.substr(0, input.find(' '))) != _commands.end())
            _commands[input.substr(0, input.find(' '))](input);
    }
}

void Server::Mediator::exit(const std::string &command)
{
    (void) command;

    // Stopping the server.
    _isRunning = false;
}

void Server::Mediator::hubs(const std::string &command)
{
    (void) command;

    std::cout << "Debuging hubs : " << std::endl;
    
    // Displaying useful data of all hubs.
    for (auto &i : _hubs) {
        std::cout << "Hub n " << i.get()->id() << std::endl;
        std::cout << "Port: " << i.get()->port() << std::endl;
        std::cout << "Number of player: " << i.get()->size() << std::endl;
    }
}

void Server::Mediator::kick(const std::string &command)
{
    // Needs care.
    auto pos = command.find(" ");

    // Getting the player to kick. Needs care. 
    std::string kick = command.substr(pos + 1, command.size());

    // Searching for the player in all hubs. Maybe add the hub number ?
    for (auto &i : _hubs)
    {
        // Check if the player is in the current hub.
        if (i.get()->isInHub(kick) == true)
        {
            // Removing the player from the match.
            i.get()->removeMember(kick);
        }
    }
}

void Server::Mediator::help(const std::string &command)
{
    (void) command;

    // Displaying help.
    std::cout << "Available commandes:\n" << std::endl;
    std::cout << "-shutdown / quit \tshutdown the server" << std::endl;
    std::cout << "-hubs \t\t\tdisplay hubs informations" << std::endl;
    std::cout << "-kick [ip] \t\tskick the ip from the server" << std::endl;
    std::cout << "-help \t\t\tdisplay the help" << std::endl;
}

void Server::Mediator::createHub(std::string ip)
{
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
        if ((*i).isOpen()) {
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
            if (i.get()->isInHub(socket->ip())) {
                i.get()->removeMember(socket->ip());
            }
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
    int port = _hubs.back().get()->port();
    std::memcpy(toSend->data, &port, sizeof(int));

    // Sending the packet to the client
    socket->write(static_cast<void *>(toSend), sizeof(Network::headerTcp));
    delete toSend;
}

// void Server::Mediator::sendEvent(Server::TcpConnection *socket, [[maybe_unused]]Network::headerTcp *packet)
// {
//     Network::headerTcp *toSend = new Network::headerTcp;
//     toSend->code = Network::SERVER_END_OF_EVENT;
//     toSend->hubNbr = 2;
//     int port = 40321;
//     std::memcpy(toSend->data, &port, sizeof(int));
//     socket->write(static_cast<void *>(toSend), sizeof(Network::headerTcp));
//     delete toSend;
// }


void Server::Mediator::setPlayerReady(Server::TcpConnection *socket, Network::headerTcp *packet)
{
    if (_hubs[packet->hubNbr - 1])
        _hubs[packet->hubNbr - 1].get()->setPlayerReady(socket->ip(), true);
    else {
        Network::headerTcp *toSend = new Network::headerTcp;
        toSend->code = Network::SERVER_END_OF_EVENT;
        std::memcpy(toSend->data, &"Can't find the hub", 19);
        socket->write(static_cast<void *>(toSend), sizeof(Network::headerTcp));
    }
}

void Server::Mediator::setPlayerNotReady(Server::TcpConnection *socket, Network::headerTcp *packet)
{
    if (_hubs[packet->hubNbr - 1])
        _hubs[packet->hubNbr - 1].get()->setPlayerReady(socket->ip(), false);
    else {
        Network::headerTcp *toSend = new Network::headerTcp;
        toSend->code = Network::SERVER_END_OF_EVENT;
        std::memcpy(toSend->data, &"Can't find the hub", 19);
        socket->write(static_cast<void *>(toSend), sizeof(Network::headerTcp));
    }
}

void Server::Mediator::sendSprite([[maybe_unused]]Server::TcpConnection *socket, [[maybe_unused]]Network::headerTcp *packet)
{
    std::cout << "Player ask sprite ... please send him :'(" << std::endl;
}

void Server::Mediator::sendEvent(Server::TcpConnection *socket, [[maybe_unused]]Network::headerTcp *packet)
{
    std::cout << "Asking for event" << std::endl;
    for (auto &i : _eventTemplate) {
        Network::headerTcp *toSend = new Network::headerTcp();
        toSend->code = Network::SERVER_SEND_KEYS;
        toSend->hubNbr = -1;
        std::cout << i.second.c_str() << std::endl;
        std::memcpy(toSend->data, i.second.c_str(), sizeof(std::strlen(i.second.c_str())));
        // socket->write(static_cast<void *>(toSend), sizeof(*toSend));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << toSend->data << std::endl;
        delete toSend;
    }
    std::cout << "finish Asking for event" << std::endl;
    Network::headerTcp *toSend = new Network::headerTcp;
    toSend->code = Network::SERVER_END_OF_EVENT;
    socket->write(static_cast<void *>(toSend), sizeof(*toSend));
    delete toSend;
    std::cout << "End !" << std::endl;
}