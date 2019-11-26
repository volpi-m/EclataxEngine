/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** ClientMediator
*/

/// \file ClientMediator.hpp
/// \author Matteo V.
/// \brief Header file for client's mediator, receive, send information to server
/// and send informations to other objects to be processes

#ifndef CLIENTMEDIATOR_HPP_
#define CLIENTMEDIATOR_HPP_

#include "UdpConnection.hpp"
#include "TcpConnection.hpp"
#include "GraphicalModule.hpp"
#include "Rfc.hpp"

/// \namespace Client
/// \brief Used for Client-related classes
namespace Client
{
    /// \class ClientMediator
    /// \brief Redirect data to be processed, send or received by other subclasses
    class ClientMediator
    {
    public:
        /// \brief Constructor
        ClientMediator();

        /// \brief Destructor
        ~ClientMediator();

        /// \brief run
        void run();

    private:
        /*! UdpConnection instance, send and receive data from server */
        Client::UdpConnection _udp;
        Client::TcpConnection _tcp;
        /*! GraphicalModule instance, create entity and draw */
        Client::GraphicalModule _graph;
    };
}

#endif /* !CLIENTMEDIATOR_HPP_ */
