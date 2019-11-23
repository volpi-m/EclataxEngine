/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** Hub declaration
*/

#pragma once

#include <vector>
#include <string>

#include "Logger.hpp"
#include "GameEngine.hpp"

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
        /*! state of the member, if he is ready or not */
        bool isReady;
    };

    /// \class Hub
    /// \brief Groupe a list of client around a game
    class Hub {

        public:
            /// \param newId : id of the hub
            /// \param creator : ip of the first Hub's member
            /// \brief constructor
            /// Initialize Hub class
            Hub(int newId, const std::string &creator);
            /// \brief destructor
            /// Destroy Hub class
            ~Hub();

            /// \brief get port of the hub
            int port() { return _port; };
            /// \brief get the number of the hub
            int id() { return _id; };

            /// \brief add an ip to the hub
            bool addMember(const std::string &newMember);
            /// \brief check if the hub is full
            bool isFull();

            /// \param ip : ip of the player
            /// \param state : state of the player
            /// \brief method for starting a game
            void setPlayerReady(const std::string &ip, bool state);

            /// \brief method for starting a game
            void startGame();

            /// \brief method for process member messages
            void processMemberMessage();

        private:
            /*! Game engine */
            Game::GameEngine _engine;
            /*! All ip of members */
            std::vector<Server::Player> _players;
            /*! number of the hub */
            int _id;
            /*! port of the hub */
            unsigned short _port;
    };
}