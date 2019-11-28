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
    /*struct Network::headerTcp *data = new Network::headerTcp();

    data->code = Network::ASK_FOR_HUB;
    std::memset(data->data, 0, 1024);

    try {
        _tcp.send((void *) data, sizeof(Network::headerTcp));
    } catch (std::exception &e) {
        throw e;
    }

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);

    char *a = static_cast<char *>(_tcp.receive());
    Network::headerTcp *s = static_cast<Network::headerTcp *>((void *) a);
    int b;
    std::memcpy(&b, s->data, sizeof(int));
    if (a)
        std::cout << s->code << " " << b << std::endl;*/

    while (!_graph.run()) {
    }
}
