/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** rfc codes
*/

#pragma once

/// \namespace Network
/// \brief Namespace used both in client and server for communication
namespace Network
{
    /// \def ADK_FOR_HUB
    /// \brief rfc code for a client asking a hub
    constexpr auto const ASK_FOR_HUB = 201;

    /// \def CLIENT_IS_READY
    /// \brief rfc code when a client is ready
    constexpr auto const CLIENT_IS_READY = 202;

    /// \def CLIENT_IS_NOT_READY
    /// \brief rfc code when a client is not ready
    constexpr auto const CLIENT_IS_NOT_READY = 203;

    /// \def CLIENT REQUEST_SPRITE
    /// \brief rfc code when a client request all needed sprites
    constexpr auto const CLIENT_REQUEST_SPRITE = 204;

    /// \def CLIENT_TICK
    /// \brief rfc code when client send keyboards events to server
    constexpr auto const CLIENT_TICK = 205;

    /// \def CLIENT_REQUIRE_KEYS
    /// \brief rfc code when a client require all key used during the game
    constexpr auto const CLIENT_REQUIRE_KEY = 206;

    /// \def CLIENT_DEBUG
    /// \brief rfc code use for debuging client
    constexpr auto const CLIENT_DEBUG = 301;

    /// \def CLIENT_ERROR
    /// \brief rfc code use when client have an error
    constexpr auto const CLIENT_ERROR = 302;


    /// \def SERVER_CLIENT_IS_IN_HUB
    /// \brief rfc code use by server to notified a client is in the hub
    constexpr auto const SERVER_CLIENT_IS_IN_HUB = 401;

    /// \def SERVER_TICK
    /// \brief code used by server to send all enemy's position
    constexpr auto const SERVER_TICK = 402;

    /// \def SERVER_NEW_PLAYER_IN_HUB
    /// \brief rfc code use by server to notified a new player entering in a hub
    constexpr auto const SERVER_NEW_PLAYER_IN_HUB = 403;

    /// \def SERVER_NEW_ENEMY_INFO
    /// \brief rfc code used by server when a new enemy (.so/.dll) has been added to the game
    constexpr auto const SERVER_NEW_ENNEMY_INFO = 404;

    /// \def SERVER_GAME_STARTING
    /// \brief rfc code used by server when a hub is full and the game will start
    constexpr auto const SERVER_GAME_STARTING = 405;

    /// \def SERVER_SEND_KEYS
    /// \brief rfc code used by client to send event when they have been requested by client
    constexpr auto const SERVER_SEND_KEYS = 406;

    /// \def SERVER_END_OF_EVENT
    /// \brief rfc code when server is done when sending events to client
    constexpr auto const SERVER_END_OF_EVENT = 407;

    /// \def SERVER_DEBUG
    /// \brief rfc code use by server for printing debug in client
    constexpr auto const SERVER_DEBUG = 501;

    /// \def SERVER_ERROR
    /// \brief rfc code use when server encountering an error
    constexpr auto const SERVER_ERROR = 502;


    /// \def TCP_CLIENT_PORT
    /// \brief port used by clients for listening server in tcp
    constexpr auto const TCP_CLIENT_PORT = 1234;

    /// \def UDP_CLIENT_PORT
    /// \brief port used by clients for listening server in udp
    constexpr auto const UDP_CLIENT_PORT = 4321;


    /// \def TCP_BUF_SIZE
    /// \brief Maximum size of a TCP buffer
    constexpr auto const TCP_BUF_SIZE = 1024;

    /// \def UDP_BUF_SIZE
    /// \brief Maximum size of a UDP buffer
    constexpr auto const UDP_BUF_SIZE = 1024;


    /// \struct headerTcp
    /// \brief data structure used when comminicating with TCP protocol
    struct headerTcp {
        /*! Protocol code cf. above to see all available codes */
        int code;
        /*! Hub number in which the specific client is */
        int hubNbr;
        /*! Data to be sent over TCP protocol */
        char data[TCP_BUF_SIZE] = {0};
    };


    /// \struct headerUdp
    /// \brief data structure used when communicating with UDP protocol
    struct headerUdp {
        /*! Protocol code, cf. above to see all available codes */
        int code;
        /*! Data to be sent over UDP protocol */
        char data[UDP_BUF_SIZE] = {0};
    };


    /// \struct Entity
    /// \brief Entity data structure used when communicating with UDP protocol to get entity status
    struct Entity {
        /*! id of the entity */
        unsigned long long id;
        /*! x coordinates of the entity */
        float x;
        /*! y coordinates of the entity */
        float y;
        /*! z coordinates of the entity */
        float z;
        /*! top value of the entity */
        float top;
        /*! left value of the entity */
        float left;
        /*! width of the texxture of the entity */
        float width;
        /*! height of the texxture of the entity */
        float height;
        /*! as the entity been deleted */
        char deleted;
        /*! texture to use */
        char texture[UDP_BUF_SIZE - (sizeof(unsigned long long) + sizeof(char) + sizeof(float) * 7)] = {0};
    };
}