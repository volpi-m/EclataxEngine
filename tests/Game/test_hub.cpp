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
    auto hub = std::shared_ptr<Server::Hub>(new Server::Hub(10, "10.10.188.288.677"));

    ASSERT_NE(hub.get(), nullptr);
}

TEST(Hub, id)
{
    Server::Hub h(1, "10.10.10.133.34");
    ASSERT_EQ(1, h.id());
}

TEST(Hub, addMember)
{
    Server::Hub h(1, "10.10.10.133.34");
    ASSERT_EQ(true, h.addMember("10.10.122.322.12"));
    h.addMember("10.10.172.322.13");
    h.addMember("10.90.122.552.12");
    ASSERT_EQ(false, h.addMember("10.10.122.322.12"));
}

TEST(Hub, isFull)
{
    Server::Hub h(1, "10.10.10.133.34");
    h.addMember("10.10.122.322.12");
    ASSERT_EQ(false, h.isFull());
    h.addMember("10.322.12.33");
    h.addMember("10.10.122.22.12");
    ASSERT_EQ(true, h.isFull());
}