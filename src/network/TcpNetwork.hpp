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
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include "TcpConnection.hpp"
#include "Logger.hpp"
#include "Rfc.hpp"

/// \namespace Server
/// \brief Used for the all server classes
namespace Server
{
    /// \class TcpNetwork
    /// \brief TcpNetwork class, used in parallel with TcpConnection class
    class TcpNetwork
    {
    public:
        /// \param io : io_context used by every I/O object of boost
        /// \param fct : function use as callback for all connections
        /// \brief Constructor
        /// Initialize network acceptor and call startAccept
        TcpNetwork(boost::asio::io_context &io, std::function<void(Server::TcpConnection *)> fct);

        /// \brief Destructor
        /// Do nothing special
        ~TcpNetwork();

        /// \brief Set a callback function to handle new connections, is called again by handleAccept
        /// and wait for an other connection to come
        void startAccept();

    private:
        /// \param co : instance of Connection Class wrapped in a smart pointer
        /// \param error : error code given by boost if something went wrong
        /// \brief Handle new connection to the server
        void handleAccept(boost::shared_ptr<Server::TcpConnection> &co, const boost::system::error_code &error);

        /*! Acceptor use by boost to accept input connections */
        tcp::acceptor _acceptor;
        /*! call back function for all connections */
        std::function<void(Server::TcpConnection*)> _callBack;
    };
}

#endif /* !TcpNetwork_HPP_ */
