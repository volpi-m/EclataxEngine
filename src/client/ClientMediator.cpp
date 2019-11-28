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

void Client::ClientMediator::run()
{
    // Connect to the server
    connectionProcedure();

    // If the client has been connected, we can start to render
    while (!_graph.run()) {
        void *packet = _udp.receive();
        if (packet)
            _graph.parsePackets(packet);
    }
}

void Client::ClientMediator::connectionProcedure()
{
    askForHub();
    // playerIsReady();
}

void Client::ClientMediator::askForHub()
{
    // sending a packet
    Network::headerTcp *header = sendEmptyTcpHeader(Network::ASK_FOR_HUB);

    // Casting the packet into the appropiate structure
    int b;
    std::memcpy(&b, header->data, sizeof(int));

    // Displaying the code
    std::cout << header->code << " code -> " << b << std::endl;

     // Freeing ressources
    delete[] header;
}

void Client::ClientMediator::playerIsReady()
{
    Network::headerTcp *header = sendEmptyTcpHeader(Network::CLIENT_IS_READY);

    std::cout << "player is ready : " << header << std::endl;
}

Network::headerTcp *Client::ClientMediator::sendEmptyTcpHeader(std::size_t code)
{
    // Creating a packet to request a hub
    struct Network::headerTcp *data = new Network::headerTcp();

    // Filling the tcp header
    data->code = code;
    std::memset(data->data, 0, 1024);

    // Sending the packet
    _tcp.send((void *)data, sizeof(Network::headerTcp));
    delete data;

    // Getting the response from the server
    char *response = _tcp.receive();
    while (!response)
        response = _tcp.receive();

    Network::headerTcp *header = static_cast<Network::headerTcp *>((void *)response);
    return header;
}