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

Server::TcpConnection::TcpConnection(boost::asio::io_context &io, 
    std::function<void(Server::TcpConnection *)> fct)
    : _socket(io), _callBack(fct), _connected(true)
{}

Server::TcpConnection::~TcpConnection() {}

boost::shared_ptr<Server::TcpConnection> Server::TcpConnection::create(boost::asio::io_context &io, 
    std::function<void(Server::TcpConnection *)> fct)
{
    return boost::shared_ptr<Server::TcpConnection>(new Server::TcpConnection(io, fct));
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
    if (error)
        disconnect(error);
}

void Server::TcpConnection::handleRead(const boost::system::error_code &error, [[maybe_unused]] const size_t b)
{
    if (error)
        disconnect(error);
    else {
        _callBack(this);
        for (size_t i = 0; i < BUFFER_SIZE; i++)
            _buf[i] = 0;
        read();
    }
}

void Server::TcpConnection::disconnect(const boost::system::error_code &error)
{
    Debug::Logger *log = Debug::Logger::getInstance(".log");
    log->generateDebugMessage(Debug::type::INFO, "Disconnect client with ip: " + _ip, "TcpConnection::disconnect");

    if (error.value() != 2) {
        log->generateDebugMessage(Debug::type::ERROR, "Error: " + error.message());
        std::cerr << "Error: " << error.message() << std::endl;
    }
    _connected = false;
    _callBack(this);
    _socket.close();
}

void Server::TcpConnection::read()
{
    _socket.async_read_some(boost::asio::buffer(_buf),
        boost::bind(&TcpConnection::handleRead, shared_from_this(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void Server::TcpConnection::write(const void *data, const std::size_t size)
{
    _socket.async_write_some(boost::asio::buffer(data, size),
        boost::bind(&TcpConnection::handleWrite, shared_from_this(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}
