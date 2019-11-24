/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** config_test
*/

#include <gtest/gtest.h>
#include "ConfReader.hpp"

TEST(ConfigTest, ValidFile)
{
    try {
        Client::ConfReader c("ressources/tests/.conf");
    } catch (Debug::MissingFileException &) {
        ASSERT_TRUE(false);
        return;
    }
    ASSERT_FALSE(false);
}

TEST(ConfigTest, InvalidFile)
{
    try {
        Client::ConfReader c("ressources/tests/ouais.conf");
    } catch (Debug::MissingFileException &) {
        ASSERT_TRUE(true);
        return;
    }
    ASSERT_FALSE(true);
}

TEST(ConfigTest, SimpleConstructor)
{
    try {
        Client::ConfReader c;
    } catch (Debug::MissingFileException &) {
        ASSERT_TRUE(true);
        return;
    }
    ASSERT_FALSE(true);
}

TEST(ConfigTest, ValidKey)
{
    Client::ConfReader conf("ressources/tests/.conf");

    std::optional<std::string> val = conf.conf("value1");
    std::optional<std::string> val2 = conf.conf("value3");

    ASSERT_TRUE(val.has_value());
    ASSERT_TRUE(val2.has_value());
}

TEST(ConfigTest, TestValue)
{
    Client::ConfReader conf("ressources/tests/.conf");

    std::optional<std::string> val1 = conf.conf("value1");
    std::optional<std::string> val2 = conf.conf("value2");
    std::optional<std::string> val3 = conf.conf("value3");

    ASSERT_TRUE(val1.value_or("error") == "hello");
    ASSERT_TRUE(val2.value_or("error") == "world");
    ASSERT_TRUE(val3.value_or("error") == "rtype");
}

TEST(ConfigTest, InvalidKey)
{
    Client::ConfReader conf("ressources/tests/.conf");

    std::optional<std::string> val = conf.conf("fdp");
    ASSERT_FALSE(val.has_value());
}

TEST(ConfigTest, ManyDoublePoint)
{
    Client::ConfReader conf("ressources/tests/.conf");

    std::optional<std::string> val = conf.conf("multiplepoint");

    ASSERT_TRUE(val.value_or("error") == "ouais:cool");
}

TEST(ConfigTest, InvalidFormatting)
{
    try {
        Client::ConfReader conf("ressources/tests/.conf");
    } catch (std::exception &) {
        ASSERT_FALSE(true);
        return;
    }
    ASSERT_TRUE(true);
}
