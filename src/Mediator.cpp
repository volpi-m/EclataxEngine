/**
 *  @file     src/engine/scenesManagement/sceneMachine/SceneStateMachine.cpp
 *  @author   tabis on the 2020-01-22
 *  @date     2020-01-22
 * 
 *  project: EclataxEngine
 * 
 */


constexpr auto const DEFAULT_SHELL_PROMPT = "$> ";

#include "Mediator.hpp"

Server::Mediator::Mediator()
    : _reader      { CONF_FILE_PATH                                                                                                                         }
    , _tcp         { _ioContext, std::function<void(Server::TcpConnection *)>(std::bind(&Server::Mediator::processTcpMessage, this, std::placeholders::_1)) }
    , _isRunning   { true                                                                                                                                   }
    , _boostThread { std::thread(&Server::Mediator::launchBoost, this)                                                                                      }
{
    readEventFile();
    _reader = Common::ConfReader(SCENE_CONF_FILE_PATH);
    _actions.emplace(Network::ASK_FOR_HUB, &Server::Mediator::askHub);
    _actions.emplace(Network::CLIENT_IS_READY, &Server::Mediator::setPlayerReady);
    _actions.emplace(Network::CLIENT_IS_NOT_READY, &Server::Mediator::setPlayerNotReady);
    _actions.emplace(Network::CLIENT_REQUIRE_KEY, &Server::Mediator::sendEvent);
    _actions.emplace(Network::CLIENT_REQUEST_SPRITE, &Server::Mediator::sendSprite);

    // Adding commands for the shell module.
    _commands.emplace("exit", std::bind(&Mediator::exit, this, std::placeholders::_1));
    _commands.emplace("hubs", std::bind(&Mediator::hubs, this, std::placeholders::_1));
    _commands.emplace("kick", std::bind(&Mediator::kick, this, std::placeholders::_1));
    _commands.emplace("help", std::bind(&Mediator::help, this, std::placeholders::_1));
}

Server::Mediator::~Mediator()
{
    // Stop boost::asio.
    _ioContext.stop();
    _boostThread.join();

    // Stoping hubs.
    for (auto &hub : _hubs)
        hub->stop();

    // Joining threads.
    for (auto &thread : _threads)
        thread.join();
}

void Server::Mediator::launchBoost()
{
    _ioContext.run();
}

void Server::Mediator::readEventFile()
{
    int value = 1;
    auto i = _reader.conf(std::to_string(value));

    for (auto i = _reader.conf(std::to_string(value)); i.has_value(); i = _reader.conf(std::to_string(value)))
    {
        _eventTemplate[value] = i.value();
        value <<= 1;
    }
}

std::vector<std::string> parseCommand(const std::string &command);

void Server::Mediator::start()
{
    std::string input;

    while (_isRunning)
    {
        // Displaying the prompt and getting the input from the user.
        std::cout << DEFAULT_SHELL_PROMPT;
        std::getline(std::cin, input);

        // Getting commands
        auto command_parameters = parseCommand(input);

        // Checking if the command exists.
        if (!command_parameters.empty() && _commands.find(command_parameters.at(0)) != _commands.end())
            _commands[command_parameters.at(0)](command_parameters);
    }
}

std::vector<std::string> Server::Mediator::parseCommand(const std::string &command)
{
    std::vector<std::string> split;
    std::size_t idx = 0;

    // Skipping first non-command characters.
    for (; !command.empty() && command[idx] <= ' '; ++idx);

    // Getting command arguments.
    for (std::size_t start = idx; command[idx]; ++idx)
    {
        for (; command[idx] > ' '; ++idx);

        // Getting the command.
        auto tmp = command.substr(start, idx - start);

        // Pushing it back to our vector.
        split.push_back(tmp);

        // Skipping non-command characters.
        for (; command[idx] && command[idx] <= ' '; ++idx);
        start = idx--;
    }

    return split;
}

void Server::Mediator::exit(const std::vector<std::string> &command)
{
    (void) command;

    // Stopping the server.
    _isRunning = false;
}

void Server::Mediator::hubs(const std::vector<std::string> &command)
{
    (void) command;

    std::cout << "Debuging hubs : " << std::endl;
    
    // Displaying useful data of all hubs.
    for (auto &hub : _hubs)
    {
        std::cout << "Hub n " << hub->id() << std::endl;
        std::cout << "Port: " << hub->port() << std::endl;
        std::cout << "Number of player: " << hub->size() << std::endl;
    }
}

void Server::Mediator::kick(const std::vector<std::string> &command)
{
    // Checking arguments
    if (command.size() != 2)
        return;

    // Searching for the player in all hubs. Maybe add the hub number ?
    for (auto &hub : _hubs)
    {
        // Check if the player is in the current hub.
        if (hub->isInHub(command.at(1)) == true)
        {
            // Removing the player from the match.
            hub->removeMember(command.at(1));
        }
    }
}

void Server::Mediator::help(const std::vector<std::string> &command)
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
    auto main_scene = _reader.conf("main_scene");

    if (!main_scene.has_value())
    {
        Debug::Logger::printDebug(Debug::ERROR, "Couldn't create the main scene, config not found.", "Server::Mediator::createHub");
        return;
    }
    _mut.lock();
    _hubs.emplace_back(std::make_unique<Server::Hub>(_hubs.size() + 1, ip, _ioContext, main_scene.value()));
    _mut.unlock();
}

int Server::Mediator::hubNumber()
{
    return _hubs.size();
}

int Server::Mediator::assignHub(std::string ip)
{
    for (auto &hub : _hubs)
    {
        if (hub->isOpen())
        {
            hub->addMember(ip);
            return (hub->id());
        }
    }
    
    createHub(ip);
    _threads.emplace_back(std::bind(&Server::Hub::start, _hubs.back().get()));
    return _hubs.size();
}

void Server::Mediator::processTcpMessage(Server::TcpConnection *socket)
{
    if (socket->state())
    {
        Network::headerTcp *h = static_cast<Network::headerTcp *>((void *)socket->buffer().data());
        if (_actions.find(h->code) != _actions.end())
            (this->*_actions[h->code])(socket, h);
    }
    else
    {
        for (auto &hub : _hubs) {
            if (hub->isInHub(socket->ip())) {
                hub->removeMember(socket->ip());
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