/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** TcpConnection
*/

/// \file TcpConnection.hpp
/// \author Mattéo V.
/// \brief Header file for TcpConnection class

#ifndef TcpConnection_HPP_
    #define TcpConnection_HPP_

#include <iostream>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

/// \def UNUSED
/// \brief attribute unused from g++
#define UNUSED __attribute__((unused))

#define BUFFER_SIZE 256

using boost::asio::ip::tcp;

/// \namespace Serv
/// \brief Used for the all server classes
namespace Server
{
    /// \class TcpConnection
    /// \brief TcpConnection class, asynchronous server, handle all I/O TcpConnections with clients
    class TcpConnection : public boost::enable_shared_from_this<TcpConnection>
    {
    public:
        ~TcpConnection();

        static boost::shared_ptr<TcpConnection> create(boost::asio::io_context &);
        tcp::socket &getSocket();
        void setIP(const std::string &ip);
        void start();

    private:
        TcpConnection(boost::asio::io_context &);
        void handleWrite(const boost::system::error_code &, size_t);
        void handleRead(const boost::system::error_code &, size_t);
        void disconnect(const boost::system::error_code &);
        void read();
        void writeback(uint, const char *, std::size_t);

        /*! Socket used for the TcpConnection with a client */
        tcp::socket _socket;
        /*! Buffer filled by received packets */
        boost::array<char, BUFFER_SIZE> _buf;
        /*! IP address of the client connected to this instance of the TcpConnection class */
        std::string _ip;
    };
}

#endif /* !TcpConnection_HPP_ */
