/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** TcpConnection
*/

/// \file TcpConnection.cpp
/// \author Matteo V.
/// \brief Implementation of TCP communication with server

#include "TcpConnection.hpp"

Client::TcpConnection::TcpConnection()
    : _conf("ressources/rtype.conf")
{
    // Get server ip and connection port from configuration file
    std::optional<std::string> ip = _conf.conf("server_ip");
    std::optional<std::string> port = _conf.conf("tcp_port");

    // Throw exception if no port nor ip has been found
    if (!ip.has_value() && !port.has_value())
        throw Debug::ConfigFileException("Missing value in config file", "TcpConnection Ctor");

    // Connect socket to server and throw if connection is impossible
    sf::Socket::Status status = _socket.connect(ip.value(), std::stoi(port.value()));
    if (status != sf::Socket::Done)
        throw Debug::TcpSocketException("Can't connect socket to server", "TcpConection Ctor");

    _socket.setBlocking(false);
}

Client::TcpConnection::~TcpConnection() {}

void Client::TcpConnection::send(const void *data, const std::size_t size)
{
    std::memcpy(_buf, data, size);
    try {
        while (_socket.send(_buf, size, _sent) != sf::Socket::Done);
    } catch (std::exception &e) {
        throw e;
    }
    _sent = 0;
}

char *Client::TcpConnection::receive()
{
    std::size_t received;
    
    if (_socket.receive(_buf, Network::TCP_BUF_SIZE, received) == sf::Socket::Done) {
        char *b = new char[received + 1];
        std::memset(b, 0, received + 1);
        std::memcpy(b, _buf, received);
        return b;
    }
    return nullptr;
}
