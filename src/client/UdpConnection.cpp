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
    : _conf("ressources/rtype.conf")
{
    // Retrieve server's ip and port from configuration file
    std::optional<std::string> ip = _conf.conf("server_ip");
    std::optional<std::string> port = _conf.conf("udp_port");

    // Throw an exception if one of the value is not present
    if (!ip.has_value() && !port.has_value())
        throw std::exception();

    // Bind udp socket to a specified port and set the socket non blocking
    _socket.bind(std::stoi(port.value()));
    _socket.setBlocking(false);
}

Client::UdpConnection::~UdpConnection() {}

void Client::UdpConnection::send(const char *data, const unsigned short port, std::size_t size)
{
    std::memcpy(_buf, data, size);
    _socket.send(_buf, size, _servIP, port);
}

char *Client::UdpConnection::receive()
{
    std::size_t received = 0;
    sf::IpAddress sender;
    unsigned short port = 0;

    if (_socket.receive(_buf, UDP_BUF_SIZE, received, sender, port) == sf::Socket::Done) {
        std::cout << sender.toString() << " said: " << _buf << std::endl;
        char *b = new char[UDP_BUF_SIZE + 1];
        std::memset(b, 0, UDP_BUF_SIZE + 1);
        std::memcpy(b, _buf, UDP_BUF_SIZE);
        return b;
    }
    return nullptr;
}
