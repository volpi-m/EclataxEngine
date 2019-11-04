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


/// \brief Constructor
/// Initialize network acceptor and call startAccept
Server::TcpNetwork::TcpNetwork(boost::asio::io_context &io)
    : _acceptor(io, tcp::endpoint(tcp::v4(), 1234))
{
    startAccept();
}


/// \brief Destructor
/// Do nothing special
Server::TcpNetwork::~TcpNetwork() {}


/// Set a callback function to handle new connections, is called again by handleAccept
/// and wait for an other connection to come
void Server::TcpNetwork::startAccept()
{
    boost::shared_ptr<Server::TcpConnection> co = Server::TcpConnection::create(_acceptor.get_executor().context());
    _acceptor.async_accept(co->getSocket(),
        boost::bind(&TcpNetwork::handleAccept, this, co, boost::asio::placeholders::error));
}


/// \param co : instance of Connection Class wrapped in a smart pointer
/// \param error : error code given by boost if something went wrong
/// Handle new connection to the server
void Server::TcpNetwork::handleAccept(
    boost::shared_ptr<Server::TcpConnection> &co,
    const boost::system::error_code &error
)
{
    if (!error) {
        const std::string ip = co->getSocket().remote_endpoint().address().to_string();
        const ushort port = co->getSocket().remote_endpoint().port();
        std::cout << "Client: " << ip << " " << port << std::endl;
        co->setIP(ip);
        co->start();
    }
    // call startAccept to handle an other connection
    startAccept();
}
