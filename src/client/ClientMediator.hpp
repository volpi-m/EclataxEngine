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

#include "Exception.hpp"
#include "UdpConnection.hpp"
#include "TcpConnection.hpp"
#include "GraphicalModule.hpp"

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
        ClientMediator() = default;

        /// \brief Destructor
        ~ClientMediator() = default;

        /// \brief run
        void run();

    private:
        /// \brief connect the client to the server
        void connectionProcedure();

        /// \brief ask the server to give a valid hub 
        void askForHub();

        /// \brief notify the server that the client is ready
        void playerIsReady();

        /// \brief send an empty tcp header and getting a response
        /// \param code : the code to send
        /// \return a pointer to a tcp header
        Network::headerTcp *sendEmptyTcpHeader(std::size_t code);

        /*! UdpConnection instance, send and receive data from server during a game */
        Client::UdpConnection _udp;
        /*! TcpConnection instance, send and receive data from server before and after a game */
        Client::TcpConnection _tcp;
        /*! GraphicalModule instance, create entity and draw */
        Client::GraphicalModule _graph;
    };
}

#endif /* !CLIENTMEDIATOR_HPP_ */
