/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** UdpConnection
*/

/// \file UdpConnection.cpp
/// \author Matteo V.
/// \brief UdpConnection class on client side, use sf::UdpSocket to send on network

#ifndef UDPCONNECTION_HPP_
#define UDPCONNECTION_HPP_

#include <iostream>
#include <array>
#include <string>
#include <fstream>
#include <exception>
#include <cstring>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "MissingFileException.hpp"

/// \def UDP_SIZE
/// \brief brief
constexpr auto const UDP_SIZE = 512;

/// \namespace Client
/// \brief Used for Client classes
namespace Client
{
    /// \class UdpConnection
    /// \brief UdpConnection class, handle UDP connection with server, uses sf::UdpSocket 
    class UdpConnection
    {
    public:
        /// \brief Constructor
        /// Bind socket, get server ip from a config file and keep it
        UdpConnection();

        /// \brief Destructor
        /// Do nothing special
        ~UdpConnection();

        /// \brief Send packets to server
        /// \param data : data to send to server
        /// \param port : port of the server you send your data to
        void send(const char *, const unsigned short);

        /// \brief Receive packets from server
        /// \return Return a string with server's IP
        std::string receive();

    private:
        /// \brief Read and stores server's IP in configuration file
        void requireIP();

        /*! Server's IP, get from a config file */
        std::string _servIP;
        /*! Udp Socket, bound to a specific IP on server */
        sf::UdpSocket _socket;
        /*! Buffer for received message */
        char _buf[UDP_SIZE];
    };
}

#endif /* !UDPCONNECTION_HPP_ */
