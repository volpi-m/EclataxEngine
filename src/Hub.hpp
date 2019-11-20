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

constexpr auto const HUBLIMIT = 4;

/// \namespace Game
/// \brief Used for the game part classes
namespace Game {

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


        private:
            /*! All ip of members */
            std::vector<std::string> _members;
            /*! number of the hub */
            int _id;
            /*! port of the hub */
            unsigned short _port;
    };
}