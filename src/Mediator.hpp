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
#include "IScene.hpp"
#include "SplashScene.hpp"
#include "Hub.hpp"
#include "Rfc.hpp"
// #include "macro.hpp"

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

            // std::unordered_map<int, std::function<void(Mediator *, const std::string &ip)>> _actions;

            /// \brief method for creating a new hub
            void createHub(std::string ip);
            /// \brief Launch Boost librairire
            void launchBoost();
            /// \brief assign a hub to the current ip. If no hub is available, it create a thread with the new hub inside.
            int assignHub(std::string ip);

    };
}