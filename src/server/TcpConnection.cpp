/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Connection
*/

/// \file TcpConnection.cpp
/// \author Mattéo V.
/// \brief Source file for TcpConnection class

#include "TcpConnection.hpp"

/// \brief constructor.
/// Initialize socket
/// \param io : boost's io_context used by every I/O object in boost::asio
Server::TcpConnection::TcpConnection(boost::asio::io_context &io)
    : _socket(io)
{}


/// \brief Destructor.
/// Do nothing special
Server::TcpConnection::~TcpConnection() {}


/// \param io : boost's io_contect used by every I/O object in boost::asio
/// \return new Connection instance as a shared pointer
/// \brief Return a new Connection instance as a shared pointer
boost::shared_ptr<Server::TcpConnection> Server::TcpConnection::create(boost::asio::io_context &io)
{
    return boost::shared_ptr<Server::TcpConnection>(new Server::TcpConnection(io));
}


/// \return Socket reference from the class
/// \brief Return the socket
tcp::socket &Server::TcpConnection::getSocket()
{
    return _socket;
}


/// \param ip : ip address of the current client connected to this instance of Connection
/// \brief Save the ip of the remote client in the instance of Connection, called in Server when the connection occurs
void Server::TcpConnection::setIP(const std::string &ip)
{
    _ip = ip;
}


/// \brief server's startup function. Called when a client is connected to bind writing and
/// reading functions to their respectives callback
void Server::TcpConnection::start()
{
    read();
}


/// \param error : error code set by boost::asio
/// \param b : number of bytes written
/// \brief Callback function used after a packet has been sent, if an error occurs, disconnect the client from the server
void Server::TcpConnection::handleWrite(const boost::system::error_code &error, [[maybe_unused]] size_t b)
{
    if (!error)
        std::cout << "Packet sent to " << _ip << std::endl;
    else
        disconnect(error);
}


/// \param error : error code set by boost::asio
/// \param b : number of bytes written
/// \brief Callback function used after a packet has been received
/// analyse the received packet to return what the client asked (if INFO_CONTACT is send, return client's contacts)
void Server::TcpConnection::handleRead(const boost::system::error_code &error, size_t b)
{
    // Babel::tcpHeader *received = static_cast<Babel::tcpHeader *>((void *)_buf.data());
    // std::cout << b << " bytes packet received from: " + _ip << std::endl;
    // std::cout << "\tCODE='" << received->code << "'" << std::endl;
    // std::cout << "\tMSG='" << received->data << "'" << std::endl;
    std::cout << _buf.data();

    for (size_t i = 0; i < BUFFER_SIZE; i++)
        _buf[i] = 0;
    if (error)
        disconnect(error);
    else
        read();
}


/// \param error : error code set by boost::asio, used to display the error message
/// \brief Show the error message and disconnect the socket
void Server::TcpConnection::disconnect(const boost::system::error_code &error)
{
    std::cout << "Disconnect client with ip: " + _ip << std::endl;

    if (error.value() != 2)
        std::cerr << "Error: " << error.message() << std::endl;
    _socket.close();
}


/// \brief Bind the read action with a callback, must be called by the callback to read again on network
void Server::TcpConnection::read()
{
    _socket.async_read_some(boost::asio::buffer(_buf),
        boost::bind(&TcpConnection::handleRead, shared_from_this(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}


/// \param code : network code to be written on the network (see Voip.hpp for all codes available)
/// \param data : string to be written on network with network code
/// \param size : size of the string to be written on network
/// \brief Write a packet on network, use the structure defined in Voip.hpp to send data
void Server::TcpConnection::writeback(uint code, const char *data, std::size_t size)
{
    char *toSend = new char(10);
    // Babel::tcpHeader *toSend = new Babel::tcpHeader();
    // toSend->code = code;
    // std::memset(&(toSend->data), 0, TCP_BUFFER_SIZE);
    // std::strcpy((char *) &(toSend->data), data);
    // std::cout << "Packet will be send to: " + _ip << " with code: " << toSend->code << " and message: '" << toSend->data << "'" << std::endl;
    _socket.async_write_some(boost::asio::buffer(static_cast<void *>(toSend), 4 + size),
        boost::bind(&TcpConnection::handleWrite, shared_from_this(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
    delete toSend;
}
