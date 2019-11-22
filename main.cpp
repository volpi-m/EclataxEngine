/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** main
*/

/// \file main.cpp
/// \author Lucas T.
/// \brief main function

#include "TcpNetwork.hpp"
#include "UdpNetwork.hpp"
#include "GameEngine.hpp"
#include "DumyScene.hpp"
#include "Breakpoint.hpp"

/// \brief main function
int main()
{
    Game::GameEngine engine;
    auto scene = std::shared_ptr<Scenes::IScene>(new Scenes::DumyScene("Dummy scene", engine.ECS()));

    Debug::Breakpoint("Fuck off", "yes");
    engine.SceneMachine()->push(scene);
    while (engine.SceneMachine()->run());
}