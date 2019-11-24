/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** ClientMediator
*/

/// \file ClientMediator.cpp
/// \author Matteo V.
/// \brief Implementation of Mediator

#include "ClientMediator.hpp"

Client::ClientMediator::ClientMediator()
{
}

Client::ClientMediator::~ClientMediator() {}

void Client::ClientMediator::run()
{
    while (!_graph.run()) {
        char *a = static_cast<char *>(_udp.receive());
        if (a)
            std::cout.write(a, std::strlen(a));
    }
}
