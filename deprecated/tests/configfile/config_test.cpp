/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** config_test
*/

#include <gtest/gtest.h>
#include "ConfReader.hpp"
#include "ConfWriter.hpp"

TEST(ConfigTest, ValidFile)
{
    try {
        Common::ConfReader c("ressources/tests/.conf");
    } catch (Debug::MissingFileException &) {
        ASSERT_TRUE(false);
        return;
    }
    ASSERT_FALSE(false);
}

TEST(ConfigTest, InvalidFile)
{
    try {
        Common::ConfReader c("ressources/tests/ouais.conf");
    } catch (Debug::MissingFileException &) {
        ASSERT_TRUE(true);
        return;
    }
    ASSERT_FALSE(true);
}

TEST(ConfigTest, SimpleConstructor)
{
    try {
        Common::ConfReader c;
    } catch (Debug::MissingFileException &) {
        ASSERT_TRUE(true);
        return;
    }
    ASSERT_FALSE(true);
}

TEST(ConfigTest, ValidKey)
{
    Common::ConfReader conf("ressources/tests/.conf");

    std::optional<std::string> val = conf.conf("value1");
    std::optional<std::string> val2 = conf.conf("value3");

    ASSERT_TRUE(val.has_value());
    ASSERT_TRUE(val2.has_value());
}

TEST(ConfigTest, TestValue)
{
    Common::ConfReader conf("ressources/tests/.conf");

    std::optional<std::string> val1 = conf.conf("value1");
    std::optional<std::string> val2 = conf.conf("value2");
    std::optional<std::string> val3 = conf.conf("value3");

    ASSERT_TRUE(val1.value_or("error") == "hello");
    ASSERT_TRUE(val2.value_or("error") == "world");
    ASSERT_TRUE(val3.value_or("error") == "rtype");
}

TEST(ConfigTest, InvalidKey)
{
    Common::ConfReader conf("ressources/tests/.conf");

    std::optional<std::string> val = conf.conf("fdp");
    ASSERT_FALSE(val.has_value());
}

TEST(ConfigTest, ManyDoublePoint)
{
    Common::ConfReader conf("ressources/tests/.conf");

    std::optional<std::string> val = conf.conf("multiplepoint");

    ASSERT_TRUE(val.value_or("error") == "ouais:cool");
}

TEST(ConfigTest, InvalidFormatting)
{
    try {
        Common::ConfReader conf("ressources/tests/.conf");
    } catch (std::exception &) {
        ASSERT_FALSE(true);
        return;
    }
    ASSERT_TRUE(true);
}

TEST(ConfigTest, writeInFile)
{
    std::unordered_map<std::string, std::string> conf;

    conf.emplace("var1", "value1");
    conf.emplace("var2", "value2");
    conf.emplace("var3", "value3");
    conf.emplace("var4", "value4");

    // Writing the configuration and reading it
    Common::ConfWriter write(conf, "ressources/tests/.confw");
    Common::ConfReader read("ressources/tests/.confw");

    ASSERT_STREQ(read.conf("var1").value().c_str(), "value1");
    ASSERT_STREQ(read.conf("var2").value().c_str(), "value2");
    ASSERT_STREQ(read.conf("var3").value().c_str(), "value3");
    ASSERT_STREQ(read.conf("var4").value().c_str(), "value4");
    remove("ressources/tests/.confw");
}