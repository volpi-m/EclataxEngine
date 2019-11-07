/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** main
*/

#include "TcpNetwork.hpp"
#include "UdpNetwork.hpp"

int main()
{
    try {
        boost::asio::io_context io;
        Server::TcpNetwork serv(io);
        // Server::UdpNetwork serv(io);
        io.run();
    } catch(const std::exception &e) {
        ;
    }
    return 0;
}
