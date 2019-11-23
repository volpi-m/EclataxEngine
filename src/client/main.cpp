/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** main
*/

/// \file main.cpp
/// \author Matteo V.
/// \brief main function for client

#include "UdpConnection.hpp"
#include "GraphicalModule.hpp"

int main()
{
    Client::GraphicalModule graph;
    sf::IntRect rect(0, 0, 532, 372);

    graph.createEntity(0, "../ressources/r-typesheet1.gif", rect);
    while (true)
        graph.run();

    // try {
    //     Client::UdpConnection c;
    //     while (true)
    //         c.receive();
    // } catch (Debug::MissingFileException &e) {
    //     e.debugErrorMessage();
    //     return 84;
    // }

    // sf::Clock clock;
    // while (true) {
    //     sf::Time t = clock.getElapsedTime();
    //     if (t.asMilliseconds() > 16) {
    //         std::cout << "Test" << std::endl;
    //         clock.restart();
    //     }
    // }

    return 0;
}
