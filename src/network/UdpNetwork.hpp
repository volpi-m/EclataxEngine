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
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include "macro.hpp"

using boost::asio::ip::udp;

/// \namespace Server
/// \brief Used for the all server classes
namespace Server
{
    /// \class UdpNetwork
    /// \brief UdpNetwork class, receive all udp connection
    class UdpNetwork
    {
    public:
        /// \param io : io_context used by every I/O object of boost
        /// \brief Constructor
        /// Initialize socket and wait for a new connection
        UdpNetwork(boost::asio::io_context &);

        /// \brief Destructor
        /// Do nothing special
        ~UdpNetwork();

    private:
        /// \brief Wait for connection and setup a callback for received message
        /// called again by handleRead to accept new packet
        void startAccept();

        /// \brief handle any received packet
        /// \param err : error code
        /// \param size : size of the packet received
        void handleRead(const boost::system::error_code &, const std::size_t);

        /// \brief callback for any sent packet
        /// \param err : error code
        /// \param size : size of the packet sent
        void handleWrite(const boost::system::error_code &, const std::size_t);

        /// \brief write packet to client
        /// \param code : packet code
        /// \param data : any other data to be send
        /// \param size : size of total data + 4 for code size
        void writeback(const uint, const char *, const std::size_t);

        /*! Socket used to receive data from udp */
        udp::socket _socket;
        /*! Connection ednpoint */
        udp::endpoint _endpoint;
        /*! Buffer containing data got from remote client */
        boost::array<char, BUFFER_SIZE> _buf;
    };
}

#endif /* !UdpNetwork_HPP_ */
