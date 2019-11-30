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

#include <chrono>
#include "Exception.hpp"
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
        ClientMediator() : _hub(0) {};

        /// \brief Destructor
        ~ClientMediator() = default;

        /// \brief run
        void run();

    private:
        /// \brief connect the client to the server
        void connectionProcedure();

        /// \brief require all keys that will be used during the game
        void requireKeyMap();

        /// \brief ask the server to give a valid hub 
        void askForHub();

        /// \brief notify the server that the client is ready
        void playerIsReady();

        /// \brief send an empty tcp header and getting a response
        /// \param code : the code to send
        /// \return a pointer to a tcp header
        Network::headerTcp *sendEmptyTcpHeader(std::size_t code);

        /// \brief send event handled by sfml to server on UDP network
        void sendEvents();

        /// \brief read UDP packet from the network, to be handled by processEvent
        void readNetwork();

        /*! UdpConnection instance, send and receive data from server during a game */
        Client::UdpConnection _udp;
        /*! TcpConnection instance, send and receive data from server before and after a game */
        Client::TcpConnection _tcp;
        /*! GraphicalModule instance, create entity and draw */
        Client::GraphicalModule _graph;
        /*! the hub the client is currently in (0 is none) */
        std::size_t _hub;
        /*! Hub port to send message */
        unsigned short _port;
    };
}

#endif /* !CLIENTMEDIATOR_HPP_ */
