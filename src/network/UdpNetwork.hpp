/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Server
*/

/// \file UdpNetwork.hpp
/// \author Mattéo V.
/// \brief Header file for UdpNetwork class

#ifndef UdpNetwork_HPP_
    #define UdpNetwork_HPP_

#include <iostream>
#include <array>
#include <functional>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <optional>

#include "macro.hpp"
#include "Rfc.hpp"

using boost::asio::ip::udp;

/// \namespace Server
/// \brief Used for the all server classes
namespace Server
{
    /// \class UdpNetwork
    /// \brief UdpNetwork class, receive all udp connection
    class UdpNetwork    {

        public:
            /// \param io : io_context used by every I/O object of boost
            /// \param callBack : callBack function
            /// \brief Constructor
            /// Initialize socket and wait for a new connection
            UdpNetwork(boost::asio::io_context &io, std::function<void(Server::UdpNetwork *)>callBack);

            /// \brief Destructor
            /// Do nothing special
            ~UdpNetwork();

            /// \brief return port of socket
            int port() const { return _socket.local_endpoint().port(); };
            /// \brief return port of the sender socket
            int remotePort() const { return _endpoint.port(); };
            /// \brief return ip of the sender socket
            std::string remoteIp() const { return _endpoint.address().to_string(); };
            // std::optional<std::string> remoteIp() const { return _remoteIp ? _remoteIp : {}; };

            /// \brief get the buffer content
            std::array<char, BUFFER_SIZE> buffer() const { return _buf; };

            /// \brief write packet to client
            /// \param ip : ip of the destination
            /// \param data : any other data to be send
            /// \param size : size of total data
            void write(const std::string &ip, const void *data, const std::size_t size);

        private:
            /// \brief Wait for connection and setup a callback for received message
            /// called again by handleRead to accept new packet
            void startAccept();

            /// \brief handle any received packet
            /// \param size : size of the packet received
            void handleRead(const std::size_t);

            /// \brief callback for any sent packet
            /// \param size : size of the packet sent
            void handleWrite(const std::size_t);

            std::string _remoteIp;

            /*! Socket used to receive data from udp */
            udp::socket _socket;
            /*! Connection endpoint */
            udp::endpoint _endpoint;
            /*! Buffer containing data got from remote client */
            std::array<char, BUFFER_SIZE> _buf;
            /*! callBack function */
            std::function<void(Server::UdpNetwork *)> _callBack;
    };
}

#endif /* !UdpNetwork_HPP_ */
