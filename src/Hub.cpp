/*
** EPITECH PROJECT, 2019
** rType
** File description:
** Hub methods
*/

#include "Hub.hpp"

Server::Hub::Hub(int newId, const std::string &creator) : _id(newId)
{
    // Debug::Logger *l = Debug::Logger::getInstance();
    // std::string msg("create hub with : ")
    // l->generateDebugMessage(Debug::type::INFO , msg + creator, "main");
    addMember(creator);
}

Server::Hub::~Hub()
{
}

bool Server::Hub::addMember(const std::string &newMember)
{
    if (isFull())
        return false;
    else {
        _players.emplace_back(Server::Player(newMember, false));
        return true;
    }
}

bool Server::Hub::isFull()
{
    if (_players.size() >= HUBLIMIT)
        return true;
    else
        return false;
}

void Server::Hub::setPlayerReady(const std::string &ip, bool state)
{
    for (auto &i : _players)
        if (i.ip == ip)
            i.isReady = state;
}