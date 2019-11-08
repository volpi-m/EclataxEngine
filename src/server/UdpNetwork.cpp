/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** UdpNetwork
*/

#include "UdpNetwork.hpp"

Server::UdpNetwork::UdpNetwork(boost::asio::io_context &io)
    : _socket(io, udp::endpoint(udp::v4(), 1111))
{
    startAccept();
}

Server::UdpNetwork::~UdpNetwork() {}

void Server::UdpNetwork::startAccept()
{
    std::cout << "startAccept" << std::endl;
    _socket.async_receive_from(boost::asio::buffer(_buf), _endpoint,
        boost::bind(&UdpNetwork::handleRead, this,
            boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Server::UdpNetwork::handleRead(const boost::system::error_code &err, [[maybe_unused]] std::size_t b)
{
    if (!err) {
        std::cout << "New client" << std::endl;
        std::cout.write(_buf.data(), b);

        for (size_t i = 0; i < BUFFER_SIZE; i++)
            _buf[i] = 0;
    }
    writeback(1, "pute", 4);
    startAccept();
}

void Server::UdpNetwork::handleWrite(const boost::system::error_code &err, [[maybe_unused]] std::size_t size)
{
    if (!err)
        std::cout << "Packet of size " << size << " sent" << std::endl;
}

void Server::UdpNetwork::writeback([[maybe_unused]] uint code, const char *data, std::size_t size)
{
    _socket.async_send_to(boost::asio::buffer(static_cast<const void *>(data), size), _endpoint,
        boost::bind(&UdpNetwork::handleWrite, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}
