/*
** EPITECH PROJECT, 2019
** rType
** File description:
** Hub methods
*/

#include "Hub.hpp"

Game::Hub::Hub(int newId, const std::string &creator) : _id(newId)
{
    // Debug::Logger *l = Debug::Logger::getInstance();
    // std::string msg("create hub with : ")
    // l->generateDebugMessage(Debug::type::INFO , msg + creator, "main");
    addMember(creator);
}

Game::Hub::~Hub()
{
}

bool Game::Hub::addMember(const std::string &newMember)
{
    if (isFull())
        return false;
    else {
        _members.push_back(newMember);
        return true;
    }
}

bool Game::Hub::isFull()
{
    if (_members.size() >= HUBLIMIT)
        return true;
    else
        return false;
}
