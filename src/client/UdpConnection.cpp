/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** UdpConnection
*/

/// \file UdpConnection.cpp
/// \author Matteo V.
/// \brief UdpConnection class on client side, use sf::UdpSocket to send on network

#include "UdpConnection.hpp"

Client::UdpConnection::UdpConnection()
{
    _socket.bind(12345);
    try {
        requireIP();
    } catch (Debug::MissingFileException &e) {
        throw e;
    }
}

Client::UdpConnection::~UdpConnection() {}

void Client::UdpConnection::send(const char *data, const unsigned short port)
{
    _socket.send(_buf, UDP_SIZE, _servIP, port);
}

std::string Client::UdpConnection::receive()
{
    std::size_t received = 0;
    sf::IpAddress sender;
    unsigned short port = 0;

    if (_socket.receive(_buf, UDP_SIZE, received, sender, port) == sf::Socket::Done)
        std::cout << sender.toString() << " said: " << _buf << std::endl;

    return std::string(_buf);
}

void Client::UdpConnection::requireIP()
{
    std::ifstream file("ressources/.conf");

    if (!file)
        throw Debug::MissingFileException("file 'ressources/.conf' not found",
            "Client::UdpConnection::requireIP");

    std::string line;
    while (std::getline(file, line)) {
        int pos = line.find_first_of(":");
        if (pos == 2 && !std::strncmp(line.c_str(), "ip", 2)) {
            _servIP = line.substr(pos + 1, line.size());
            std::cout << _servIP << std::endl;
        }
    }
}
