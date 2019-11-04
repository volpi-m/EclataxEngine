/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Server
*/

/// \file TcpNEtwork.hpp
/// \author Mattéo V.
/// \brief Header file for TcpNetwork class

#ifndef TcpNetwork_HPP_
    #define TcpNetwork_HPP_

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include "TcpConnection.hpp"

/// \namespace Server
/// \brief Used for the all server classes
namespace Server
{
    /// \class Server
    /// \brief Server class, used in parallel with Connection class
    class TcpNetwork
    {
    public:
        TcpNetwork(boost::asio::io_context &);
        ~TcpNetwork();

    private:
        void startAccept();
        void handleAccept(boost::shared_ptr<Server::TcpConnection> &, const boost::system::error_code &);

        /*! Acceptor use by boost to accept input connections */
        tcp::acceptor _acceptor;
    };
}

#endif /* !TcpNetwork_HPP_ */
