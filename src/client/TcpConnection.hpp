/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** TcpConnection
*/

/// \file TcpConnection.hpp
/// \author Matteo V.
/// \brief Header file for TCP communication with server

#ifndef TCPCONNECTION_HPP_
#define TCPCONNECTION_HPP_

#include <SFML/Network.hpp>
#include <cstring>
#include "ConfReader.hpp"
#include "Rfc.hpp"
#include "ConfigFileException.hpp"
#include "TcpSocketException.hpp"

namespace Client
{
    /// \class TcpConnection
    /// \brief Handle TCP connection with server
    class TcpConnection
    {
    public:
        /// \brief Constructor
        /// Require server's IP and open connection
        TcpConnection();

        /// \brief Destructor
        ~TcpConnection();

        /// \brief Send message to server
        /// \param data : packet to send to server
        /// \param size : size of the buffer
        void send(const void *, const std::size_t);

        /// \brief Recieve message from server
        /// \return Pointer to what server send
        char *receive();

    private:
        /*! Configuration file parser */
        Common::ConfReader _conf;
        /*! TCP Socket, used for client-server communication */
        sf::TcpSocket _socket;
        /*! Keep track of packet sending with non-blocking sfml */
        std::size_t _sent;
        /*! Buffer */
        char _buf[Network::TCP_BUF_SIZE + sizeof(int) * 2];
    };
}

#endif /* !TCPCONNECTION_HPP_ */
