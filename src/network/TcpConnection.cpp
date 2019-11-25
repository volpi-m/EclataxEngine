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
    std::function<void(const boost::system::error_code &, std::array<char, BUFFER_SIZE>)> fct)
    : _socket(io), _callBack(fct)
{}

Server::TcpConnection::~TcpConnection() {}

boost::shared_ptr<Server::TcpConnection> Server::TcpConnection::create(boost::asio::io_context &io, 
    std::function<void(const boost::system::error_code &, std::array<char, BUFFER_SIZE>)> fct)
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
    if (!error) {
        Debug::Logger *log = Debug::Logger::getInstance(".log");
        log->generateDebugMessage(Debug::type::INFO, "Packet sent to " + _ip, "TcpConnection::handleWrite");
    }
    else
        disconnect(error);
}

void Server::TcpConnection::handleRead(const boost::system::error_code &error, [[maybe_unused]] const size_t b)
{
    _callBack(error, _buf);
    for (size_t i = 0; i < BUFFER_SIZE; i++)
        _buf[i] = 0;
    if (error)
        disconnect(error);
    else
        read();
}

void Server::TcpConnection::disconnect(const boost::system::error_code &error)
{
    Debug::Logger *log = Debug::Logger::getInstance(".log");
    log->generateDebugMessage(Debug::type::INFO, "Disconnect client with ip: " + _ip, "TcpConnection::disconnect");

    if (error.value() != 2) {
        log->generateDebugMessage(Debug::type::ERROR, "Error: " + error.message());
        std::cerr << "Error: " << error.message() << std::endl;
    }
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
    // Babel::tcpHeader *toSend = new Babel::tcpHeader();
    // toSend->code = code;
    // std::memset(&(toSend->data), 0, TCP_BUFFER_SIZE);
    // std::strcpy((char *) &(toSend->data), data);
    // std::cout << "Packet will be send to: " + _ip << " with code: " << toSend->code << " and message: '" << toSend->data << "'" << std::endl;
    _socket.async_write_some(boost::asio::buffer(data, size),
        boost::bind(&TcpConnection::handleWrite, shared_from_this(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}
