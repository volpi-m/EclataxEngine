/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** main
*/

/// \file main.cpp
/// \author Lucas T.
/// \brief main function

#include <cstdlib>
#include <ctime>

#include "Mediator.hpp"
#include "TcpNetwork.hpp"
#include "UdpNetwork.hpp"
#include "GameEngine.hpp"
#include "MainScene.hpp"
#include "Breakpoint.hpp"

/// \brief main function
int main()
{
    std::srand(std::time(nullptr));
    Server::Mediator m;

    try
    {
        m.start();
    }
    catch(const Debug::Exception &e)
    {
        e.debugErrorMessage();
    }
}