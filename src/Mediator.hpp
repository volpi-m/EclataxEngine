/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** Mediator definition
*/

#pragma once

#include "GameEngine.hpp"
#include "TcpNetwork.hpp"
#include "UdpNetwork.hpp"
#include "Logger.hpp"
#include "IScene.hpp"
#include "SplashScene.hpp"

namespace rType {

    class Mediator {
        public:
            Mediator();
            ~Mediator();

        private:
            Game::GameEngine engine;

            void start();
    };
}