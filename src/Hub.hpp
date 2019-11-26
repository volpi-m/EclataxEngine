/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** Hub declaration
*/

#pragma once

#include <vector>
#include <string>
#include <boost/asio.hpp>

#include "Logger.hpp"
#include "GameEngine.hpp"
#include "UdpNetwork.hpp"
#include "Rfc.hpp"

constexpr auto const HUBLIMIT = 4;

/// \namespace Server
/// \brief Used for the all server classes
namespace Server {

    /// \class Player
    /// \brief Caracteristics of member of a hub
    struct Player
    {
        Player(std::string ip, bool isReady) : ip(ip), isReady(isReady) {};
        /*! ip of the member */
        std::string ip;
        /*! port of the member */
        int port;
        /*! state of the member, if he is ready or not */
        bool isReady;
    };

    /// \class Hub
    /// \brief Groupe a list of client around a game
    class Hub {

        public:
            /// \param newId : id of the hub
            /// \param creator : ip of the first Hub's member
            /// \param ioContexte : io contexte for boost
            /// \brief constructor
            /// Initialize Hub class
            Hub(int newId, const std::string &creator, boost::asio::io_context &ioContext);
            /// \brief destructor
            /// Destroy Hub class
            ~Hub();

            /// \brief get port of the hub
            int port() const { return _port; };
            /// \brief get the number of the hub
            int id() const { return _id; };

            /// \brief add an ip to the hub
            bool addMember(const std::string &newMember);
            /// \brief check if the hub is full
            bool isFull();

            /// \param ip : ip of the player
            /// \param state : state of the player
            /// \brief method for starting a game
            void setPlayerReady(const std::string &ip, bool state);
            /// \brief method for starting a game
            void startGame(); // to implement
            /// \param code : code for the message
            /// \param msg : message to send
            /// \param size : size of the message
            /// \brief method for send message to all player of the hub
            void sendToAllPlayer(const uint code, void *msg, const std::size_t size);
            /// \param udp : udp object
            /// \brief call back method call when an udp message is received
            void processUdpMessage(Server::UdpNetwork *udp);

        private:
            /*! Game engine */
            Game::GameEngine _engine;
            /*! Object for handling udp dialogue */
            Server::UdpNetwork _udp;
            /*! number of the hub */
            int _id;
            /*! port of the hub */
            unsigned short _port;
            /*! All ip of members */
            std::vector<Server::Player> _players;
    };
}