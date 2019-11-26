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
    struct Network::headerTcp *data = new Network::headerTcp();

    data->code = Network::ASK_FOR_HUB;
    std::memset(data->data, 0, 1024);

    _tcp.send((void *) data, sizeof(Network::headerTcp));

    // while (!_graph.run()) {
    //     char *a = static_cast<char *>(_tcp.receive());
    //     if (a)
    //         std::cout.write(a, std::strlen(a));
    // }
}
