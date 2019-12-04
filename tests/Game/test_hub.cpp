/*
** EPITECH PROJECT, 2019
** rType - unit test
** File description:
** Unit test for hub object
*/

#include <gtest/gtest.h>

#include "Hub.hpp"

TEST(Hub, instanciation)
{
    boost::asio::io_context ioContext;
    auto hub = std::shared_ptr<Server::Hub>(new Server::Hub(10, "10.10.188.288", ioContext));

    ASSERT_NE(hub.get(), nullptr);
}

TEST(Hub, id)
{
    boost::asio::io_context ioContext;
    auto h = std::shared_ptr<Server::Hub>(new Server::Hub(1, "10.10.188.288", ioContext));
    ASSERT_EQ(1, h.get()->id());
}

TEST(Hub, size)
{
    boost::asio::io_context ioContext;
    auto h = std::shared_ptr<Server::Hub>(new Server::Hub(1, "10.10.188.288", ioContext));
    ASSERT_EQ(1, h.get()->size());
}

TEST(Hub, isInHub)
{
    boost::asio::io_context ioContext;
    auto h = std::shared_ptr<Server::Hub>(new Server::Hub(1, "10.10.188.288", ioContext));
    ASSERT_EQ(true, h.get()->isInHub("10.10.188.288"));
}

TEST(Hub, addMember)
{
    boost::asio::io_context ioContext;
    auto h = std::shared_ptr<Server::Hub>(new Server::Hub(1, "10.10.188.288", ioContext));
    ASSERT_EQ(true, h.get()->addMember("10.10.122.322.12"));
    h.get()->addMember("10.10.172.322.13");
    h.get()->addMember("10.90.122.552.12");
    ASSERT_EQ(false, h.get()->addMember("10.10.122.322.12"));
}

TEST(Hub, removeMember)
{
    boost::asio::io_context ioContext;
    auto h = std::shared_ptr<Server::Hub>(new Server::Hub(1, "10.10.188.288", ioContext));
    h.get()->addMember("10.10.172.322.13");
    ASSERT_EQ(true, h.get()->isInHub("10.10.172.322.13"));
    h.get()->removeMember("10.10.172.322.13");
    ASSERT_EQ(false, h.get()->isInHub("10.10.172.322.13"));
}

TEST(Hub, isOpen)
{
    boost::asio::io_context ioContext;
    auto h = std::shared_ptr<Server::Hub>(new Server::Hub(1, "10.10.188.288", ioContext));
    ASSERT_EQ(true, h.get()->isOpen());
    h.get()->addMember("10.10.172.322.13");
    h.get()->addMember("10.10.172.342.13");
    h.get()->addMember("10.10.172.212.13");
    ASSERT_EQ(false, h.get()->isOpen());
}

TEST(Hub, isRunning)
{
    boost::asio::io_context ioContext;
    auto h = std::shared_ptr<Server::Hub>(new Server::Hub(1, "10.10.188.288", ioContext));
    ASSERT_EQ(true, h.get()->isRunning());
}

TEST(Hub, gameState)
{
    boost::asio::io_context ioContext;
    auto h = std::shared_ptr<Server::Hub>(new Server::Hub(1, "10.10.188.288", ioContext));
    ASSERT_EQ(false, h.get()->gameState());
}