/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Server
*/

/// \file TcpNetwork.cpp
/// \author Matteo V.
/// \brief TcpNetwork  class

#include "TcpNetwork.hpp"

Server::TcpNetwork::TcpNetwork(boost::asio::io_context &io, 
    std::function<void(Server::TcpConnection *)> fct)
    : _acceptor(io, tcp::endpoint(tcp::v4(), Network::TCP_CLIENT_PORT)) , _callBack(fct) //change port
{
    startAccept();
}

Server::TcpNetwork::~TcpNetwork() {}

void Server::TcpNetwork::startAccept()
{
    boost::shared_ptr<Server::TcpConnection> co = Server::TcpConnection::create(_acceptor.get_executor().context(), _callBack);
    _acceptor.async_accept(co->getSocket(),
        boost::bind(&TcpNetwork::handleAccept, this, co, boost::asio::placeholders::error));
}

void Server::TcpNetwork::handleAccept(
    boost::shared_ptr<Server::TcpConnection> &co,
    const boost::system::error_code &error
)
{
    if (!error) {
        const std::string ip = co->getSocket().remote_endpoint().address().to_string();
        const ushort port = co->getSocket().remote_endpoint().port();
        Debug::Logger *log = Debug::Logger::getInstance(".log");
        log->generateDebugMessage(Debug::type::INFO, "Client: " + ip + ", port: " + std::to_string(port), "TcpNetwork::handlAccept");
        co->setIP(ip);
        co->start();
    }
    // call startAccept to handle an other connection
    startAccept();
}
