/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** Hub declaration
*/

#pragma once

#include <list>
#include <string>
#include <cstring>
#include <boost/asio.hpp>
#include <optional>

#include "Logger.hpp"
#include "GameEngine.hpp"
#include "UdpNetwork.hpp"
#include "Rfc.hpp"
#include "AScene.hpp"
#include "Level1Scene.hpp"
#include "SplashScene.hpp"
#include "HubLoadingScene.hpp"
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
            /// \brief get the number of player in the hub
            int size() const { return _players.size(); };
            /// \brief get the number of player in the hub
            bool isRunning() const { return !_stoped; };
            /// \brief get the number of player in the hub
            bool gameState() const { return _isPlaying; };

            /// \param ip : ip of the removed member
            /// \return true or false if the player is remove or not
            /// \brief remove a player from the hub
            bool removeMember(const std::string &ip);
            /// \param ip : ip of the new member
            /// \brief add a player to the hub
            bool addMember(const std::string &ip);
            /// \brief check if the hub is open or not
            bool isOpen();
            /// \brief start a hub
            void start();
            /// \brief stop a hub
            /// \it is only use when the server is shutdown
            void stop();
            /// \param udp : udp object
            /// \brief call back method call when an udp message is received
            void processUdpMessage(Server::UdpNetwork *udp);
            /// \brief check if all player is ready
            bool allIsReady();
            /// \brief check if ip is a player in the hub
            bool isInHub(const std::string &ip);
            /// \param ip : ip of the player
            /// \param state : state of the player
            /// \brief method for starting a game
            void setPlayerReady(const std::string &ip, bool state);


        private:
            /*! if the hub as to be stopped */
            bool _stoped;
            /*! if a game is launch in hub */
            bool _isPlaying;
            /*! mutex for hub thread */
            std::mutex _mutex;
            /*! condittion variable for hub thread */
            std::condition_variable _cond_var;
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
            /*! queue of all event get in the hub */
            std::queue<std::pair<int, size_t>> _event;
            /*! Map of all actions when you received a udp message from client */
            std::unordered_map<int, std::function<void(Server::UdpNetwork *socket, Network::headerUdp *packet)>> _actions;

            /// \brief method for starting a game
            void startGame();
            /// \param msg : message to send
            /// \param size : size of the message
            /// \brief method for send message to all player of the hub
            void sendToAllPlayer(void *msg, const std::size_t size);
            /// \param socket : socket udp
            /// \param packet : packet send
            /// \brief method for save an event comming from 
            void addEvent(Server::UdpNetwork *socket, Network::headerUdp *packet);
            /// \param socket : socket udp
            /// \param packet : packet send
            /// \brief method call when a player encounter a probleme
            void playerError(Server::UdpNetwork *socket, Network::headerUdp *packet);
            /// \brief method call for sending entities for all player
            void sendEntity(Network::Entity &e);
            /// \brief method setting all player state to false
            void initStatePlayers();
            /// \brief handle event for hub
            void handleEvent();
    };
}