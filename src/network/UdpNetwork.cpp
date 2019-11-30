/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** UdpNetwork
*/

#include "UdpNetwork.hpp"

Server::UdpNetwork::UdpNetwork(boost::asio::io_context &io, std::function<void(Server::UdpNetwork *)> callBack)
    : _socket(io, udp::endpoint(udp::v4(), 0)), _callBack(callBack)
{
    startAccept();
}

Server::UdpNetwork::~UdpNetwork() {}

void Server::UdpNetwork::startAccept()
{
    _socket.async_receive_from(boost::asio::buffer(_buf), _endpoint,
        boost::bind(&UdpNetwork::handleRead, this,
            boost::asio::placeholders::bytes_transferred));
}

void Server::UdpNetwork::handleRead([[maybe_unused]] const std::size_t size)
{
    _callBack(this);
    for (size_t i = 0; i < BUFFER_SIZE; i++)
        _buf[i] = 0;
    startAccept();
}

void Server::UdpNetwork::handleWrite([[maybe_unused]] const std::size_t size)
{ }

void Server::UdpNetwork::write(const std::string &ip, const void *data, const std::size_t size)
{
    udp::endpoint destination(boost::asio::ip::address::from_string(ip.data()), Network::UDP_CLIENT_PORT);
    _socket.async_send_to(boost::asio::buffer(data, size), destination,
        boost::bind(&UdpNetwork::handleWrite, this,
            boost::asio::placeholders::bytes_transferred));
}
