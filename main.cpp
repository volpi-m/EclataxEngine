/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** main
*/

#include "TcpNetwork.hpp"
#include "UdpNetwork.hpp"
#include "GameEngine.hpp"
#include "DumyScene.hpp"

int main()
{
    Game::GameEngine engine;

    auto scene = std::shared_ptr<Scenes::IScene>(new Scenes::DumyScene);
    engine.SceneManager().push(scene);
    engine.SceneManager().run();
}