/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** main
*/

/// \file main.cpp
/// \author Matteo V.
/// \brief main function for client

#include "ClientMediator.hpp"

int main()
{
    try {
        Client::ClientMediator m;
        m.run();
    } catch (Debug::Exception &e) {
        e.debugErrorMessage();
    }
    return 0;
}
