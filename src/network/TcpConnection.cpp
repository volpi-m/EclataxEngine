/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Connection
*/

/// \file TcpConnection.cpp
/// \author Mattéo V.
/// \brief Source file for TcpConnection class

#include "TcpConnection.hpp"

Server::TcpConnection::TcpConnection(boost::asio::io_context &io)
    : _socket(io)
{}

Server::TcpConnection::~TcpConnection() {}

std::shared_ptr<Server::TcpConnection> Server::TcpConnection::create(boost::asio::io_context &io)
{
    return std::shared_ptr<Server::TcpConnection>(new Server::TcpConnection(io));
}

tcp::socket &Server::TcpConnection::getSocket()
{
    return _socket;
}

void Server::TcpConnection::setIP(const std::string &ip)
{
    _ip = ip;
}

void Server::TcpConnection::start()
{
    read();
}

void Server::TcpConnection::handleWrite(const boost::system::error_code &error, [[maybe_unused]] const size_t b)
{
    if (!error)
        std::cout << "Packet sent to " << _ip << std::endl;
    else
        disconnect(error);
}

void Server::TcpConnection::handleRead(const boost::system::error_code &error, [[maybe_unused]] const size_t b)
{
    // Babel::tcpHeader *received = static_cast<Babel::tcpHeader *>((void *)_buf.data());
    // std::cout << b << " bytes packet received from: " + _ip << std::endl;
    // std::cout << "\tCODE='" << received->code << "'" << std::endl;
    // std::cout << "\tMSG='" << received->data << "'" << std::endl;
    std::cout << _buf.data();

    for (size_t i = 0; i < BUFFER_SIZE; i++)
        _buf[i] = 0;
    if (error)
        disconnect(error);
    else
        read();
}

void Server::TcpConnection::disconnect(const boost::system::error_code &error)
{
    std::cout << "Disconnect client with ip: " + _ip << std::endl;

    if (error.value() != 2)
        std::cerr << "Error: " << error.message() << std::endl;
    _socket.close();
}

void Server::TcpConnection::read()
{
    _socket.async_read_some(boost::asio::buffer(_buf),
        boost::bind(&TcpConnection::handleRead, shared_from_this(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void Server::TcpConnection::writeback([[maybe_unused]] const uint code, [[maybe_unused]] const char *data, const std::size_t size)
{
    char *toSend = new char(10);
    // Babel::tcpHeader *toSend = new Babel::tcpHeader();
    // toSend->code = code;
    // std::memset(&(toSend->data), 0, TCP_BUFFER_SIZE);
    // std::strcpy((char *) &(toSend->data), data);
    // std::cout << "Packet will be send to: " + _ip << " with code: " << toSend->code << " and message: '" << toSend->data << "'" << std::endl;
    _socket.async_write_some(boost::asio::buffer(static_cast<void *>(toSend), 4 + size),
        boost::bind(&TcpConnection::handleWrite, shared_from_this(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
    delete toSend;
}
