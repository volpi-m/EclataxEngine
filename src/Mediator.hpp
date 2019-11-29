/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** Mediator definition
*/

/// \file Mediator.hpp
/// \author Arthur L.
/// \brief Mediator declaration

#pragma once

#include <thread>

#include "TcpNetwork.hpp"
#include "UdpNetwork.hpp"
#include "Logger.hpp"
#include "Hub.hpp"
#include "Rfc.hpp"

/// \namespace Server
/// \brief Used for the all server classes
namespace Server {

    /// \class Mediator
    /// \brief Encapsulate interaction between all elements of rType game
    class Mediator {

        public:
            /// \brief constructor
            /// Initialize Mediator class
            Mediator();
            /// \brief destructor
            /// Destroy Mediator class
            ~Mediator();

            /// \brief return number of hub
            int hubNumber();
            /// \brief method for starting the Mediator
            void start();
            /// \param socket pointer to the received socket
            /// \brief treat all Tcp message received
            void processTcpMessage(Server::TcpConnection *socket);

        private:
            /*! Boost contexte */
            boost::asio::io_context _ioContext;
            /*! Object handling tcp dialogue */
            Server::TcpNetwork _tcp;
            /*! Mediator mutex */
            std::mutex _mut;
            /*! Thread for running boost */
            std::thread _boostThread;
            /*! Thread list of all hub */
            std::vector<std::thread> _threads;
            /*! List of hub */
            std::vector<std::unique_ptr<Server::Hub>> _hubs;
            /*! state of the server */
            bool _isRunning;
            /*! Map of all actions when you received a tcp message from client */
            std::unordered_map<int, std::function<void(Server::TcpConnection *socket, Network::headerTcp *packet)>> _actions;

            /// \param ip ip of the hub creator
            /// \brief method for creating a new hub
            void createHub(std::string ip);
            /// \brief Launch Boost librairire
            void launchBoost();
            /// \param ip ip of the asking client
            /// \return return number of the assigned hub
            /// \brief assign a hub to the current ip. If no hub is available, it create a thread with the new hub inside.
            int assignHub(std::string ip);
            /// \param socket pointer to the received socket
            /// \param packet packet send by client
            /// \brief method call when client ask a hub
            void askHub(Server::TcpConnection *socket, Network::headerTcp *packet);
            /// \param socket pointer to the received socket
            /// \param packet packet send by client
            /// \brief method call when client is ready
            void setPlayerReady(Server::TcpConnection *socket, Network::headerTcp *packet);
            /// \param socket pointer to the received socket
            /// \param packet packet send by client
            /// \brief method call when client is ready
            void setPlayerNotReady(Server::TcpConnection *socket, Network::headerTcp *packet);
    };
}