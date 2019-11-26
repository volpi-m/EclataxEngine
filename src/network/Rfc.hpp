/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** rfc codes
*/

#pragma once

/// \def rfc code for a client asking a hub
constexpr auto const ASK_FOR_HUB = 201;
/// \def rfc code when a client is ready
constexpr auto const CLIENT_IS_READY = 202;
/// \def rfc code when a client is not ready
constexpr auto const CLIENT_IS_NOT_READY = 203;
/// \def rfc code when a client request all needed sprites
constexpr auto const CLIENT_REQUEST_SPRITE = 204;
constexpr auto const CLIENT_TICK = 205;
/// \def rfc code use for debuging client
constexpr auto const CLIENT_DEBUG = 206;

/// \def rfc code use when client have an error
constexpr auto const CLIENT_ERROR = 300;


/// \def rfc code use by server to notified a client is in the hub
constexpr auto const SERVER_CLIENT_IS_IN_HUB = 401;
constexpr auto const SERVER_TICK = 402;
/// \def rfc code use by server to notified a new player entering in a hub
constexpr auto const SERVER_NEW_PLAYER_IN_HUB = 403;
constexpr auto const SERVER_NEW_ENNEMY_INFO = 404;
/// \def rfc code use by server for printing debug in client
constexpr auto const SERVER_DEBUG = 406;

/// \def rfc code use when server encountering an error
constexpr auto const SERVER_ERROR = 501;

/// \def port used by clients
constexpr auto const CLIENT_PORT = 1234;

namespace Server {

    struct header {
        int code;
        void *data;
    };


}