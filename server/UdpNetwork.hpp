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

#define BUFFER_SIZE 256

using boost::asio::ip::udp;

/// \namespace Server
/// \brief Used for the all server classes
namespace Server
{
    /// \class UdpNetwork
    /// \brief UdpNetwork class
    class UdpNetwork
    {
    public:
        UdpNetwork(boost::asio::io_context &);
        ~UdpNetwork();

    private:
        void startAccept();
        void handleRead(const boost::system::error_code &, const std::size_t);
        void handleWrite(const boost::system::error_code &, std::size_t);
        void writeback(uint, const char *, std::size_t);
        void disconnect(const boost::system::error_code &);

        udp::socket _socket;
        udp::endpoint _endpoint;
        boost::array<char, BUFFER_SIZE> _buf;
    };
}

#endif /* !UdpNetwork_HPP_ */
