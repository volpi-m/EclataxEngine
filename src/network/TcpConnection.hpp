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
#include <array>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "macro.hpp"

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
        /// \brief Destructor.
        /// Do nothing special
        ~TcpConnection();

        /// \param io : boost's io_contect used by every I/O object in boost::asio
        /// \return new Connection instance as a shared pointer
        /// \brief Return a new Connection instance as a shared pointer
        static std::shared_ptr<TcpConnection> create(boost::asio::io_context &);

        /// \return Socket reference from the class
        /// \brief Return the socket
        tcp::socket &getSocket();

        /// \param ip : ip address of the current client connected to this instance of Connection
        /// \brief Save the ip of the remote client in the instance of Connection, called in Server when the connection occurs
        void setIP(const std::string &ip);

        /// \brief server's startup function. Called when a client is connected to bind writing and
        /// reading functions to their respectives callback
        void start();

    private:
        /// \brief constructor.
        /// Initialize socket
        /// \param io : boost's io_context used by every I/O object in boost::asio
        TcpConnection(boost::asio::io_context &);

        /// \param error : error code set by boost::asio
        /// \param b : number of bytes written
        /// \brief Callback function used after a packet has been sent, if an error occurs, disconnect the client from the server
        void handleWrite(const boost::system::error_code &, const size_t);

        /// \param error : error code set by boost::asio
        /// \param b : number of bytes written
        /// \brief Callback function used after a packet has been received
        /// analyse the received packet to return what the client asked (if INFO_CONTACT is send, return client's contacts)
        void handleRead(const boost::system::error_code &, const size_t);

        /// \param error : error code set by boost::asio, used to display the error message
        /// \brief Show the error message and disconnect the socket
        void disconnect(const boost::system::error_code &);

        /// \brief Bind the read action with a callback, must be called by the callback to read again on network
        void read();

        /// \param code : network code to be written on the network (see Voip.hpp for all codes available)
        /// \param data : string to be written on network with network code
        /// \param size : size of the string to be written on network
        /// \brief Write a packet on network, use the structure defined in Voip.hpp to send data
        void writeback(const uint, const char *, const std::size_t);

        /*! Socket used for the TcpConnection with a client */
        tcp::socket _socket;
        /*! Buffer filled by received packets */
        std::array<char, BUFFER_SIZE> _buf;
        /*! IP address of the client connected to this instance of the TcpConnection class */
        std::string _ip;
    };
}

#endif /* !TcpConnection_HPP_ */
