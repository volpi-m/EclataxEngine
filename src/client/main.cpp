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
    try {
        Client::UdpConnection udp;
        Client::GraphicalModule graph;

        while (!graph.run())
            udp.receive();
    } catch (Debug::MissingFileException &e) {
        e.debugErrorMessage();
        return 84;
    }

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
