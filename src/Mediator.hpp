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

#include "GameEngine.hpp"
#include "TcpNetwork.hpp"
#include "UdpNetwork.hpp"
#include "Logger.hpp"
#include "IScene.hpp"
#include "SplashScene.hpp"

/// \namespace Game
/// \brief Used for the game part classes
namespace Game {

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

        private:
            /*! The game engine */
            Game::GameEngine engine;

            /// \brief method for starting the Mediator
            void start();
            /// \brief method for starting a game
            void startGame();
            /// \brief method for creating a new hub
            void createHub();

    };
}