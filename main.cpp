/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** main
*/

/// \file main.cpp
/// \author Lucas T.
/// \brief main function

#include "Mediator.hpp"
#include "TcpNetwork.hpp"
#include "UdpNetwork.hpp"
#include "GameEngine.hpp"
#include "DumyScene.hpp"
#include "Breakpoint.hpp"

/// \brief main function
int main()
{
    Server::Mediator m;
    m.start();
    // Game::GameEngine engine;
    // auto scene = std::shared_ptr<Scenes::IScene>(new Scenes::DumyScene("Dummy scene", engine.ECS()));

    // engine.SceneMachine()->push(scene);
    // while (engine.SceneMachine()->run());

    // Server::UdpNetwork network();

    // network.write("127.0.0.1", , sizeof());
}