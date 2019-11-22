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

            /// \brief create a hub for player
            /// The hub is create in a different thread
            void createHub(const std::string &ip);
            /// \brief Launch Boost librairire
            void launchBoost();

        private:
            /*! Boost contexte */
            boost::asio::io_context _ioContext;
            /*! Object handling tcp dialogue */
            Server::TcpNetwork _tcp;
            /*! Thread for running boost */
            std::thread _boostThread;
            /*! List of hub */
            std::vector<Server::Hub> _hubs;


            /// \brief method for starting the Mediator
            void start();
            /// \brief method for creating a new hub
            void createHub();

    };
}