//
// Created by tabis on 10/10/2019.
//

#include "Logger.hpp"
#include <gtest/gtest.h>

TEST(LoggerTests, debugMessageOnStdout)
{
    Debug::Logger *log = Debug::Logger::getInstance(Debug::STANDARD, Debug::Flags::fatal_off);
    testing::internal::CaptureStdout();
    std::string output;

    log->generateDebugMessage(Debug::DEBUG, "debug message", "test::debugMessageOnStdout");

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    output = testing::internal::GetCapturedStdout();
    std::size_t pos = output.find(")");
    std::string str = output.substr(pos + 2);
    ASSERT_STREQ("\033[m[Debug]\033[0;36m debug message\033[m in \033[0;35mtest::debugMessageOnStdout\033[m\n", str.c_str());
}

TEST(LoggerTests, debugMessageInFile)
{
    Debug::Logger *log = Debug::Logger::getInstance("output.txt");
    std::string output;

    log->switchMode(Debug::FILE, "output.txt");
    log->generateDebugMessage(Debug::INFO, "Info message", "test::debugMessageInFile");

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::fstream stream("output.txt", std::fstream::in);
    if (!stream.is_open() || !getline(stream, output)) {
        ASSERT_NO_FATAL_FAILURE("File could not open");
        return;
    }
    stream.close();
    remove("output.txt");
    std::size_t pos = output.find(")");
    std::string str = output.substr(pos + 2);
    ASSERT_STREQ("[Info] Info message in test::debugMessageInFile", str.c_str());
}

TEST(LoggerTests, switchModeTest)
{
    Debug::Logger *log = Debug::Logger::getInstance("output.txt");
    std::string output;
    testing::internal::CaptureStdout();

    log->switchMode(Debug::STANDARD);
    log->generateDebugMessage(Debug::INFO, "Info message", "test::switchModeTest");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    output = testing::internal::GetCapturedStdout();
    std::size_t pos = output.find(")");
    std::string str = output.substr(pos + 2);
    ASSERT_STREQ("\033[m\033[0;32m[Info]\033[0;36m Info message\033[m in \033[0;35mtest::switchModeTest\033[m\n", str.c_str());
}

TEST(LoggerTests, switchModeTestInverse)
{
    Debug::Logger *log = Debug::Logger::getInstance();
    std::string output;

    log->switchMode(Debug::FILE);
    log->generateDebugMessage(Debug::INFO, "Info message", "test::switchModeTestInverse");
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::fstream stream("output.txt", std::fstream::in);
    if (!stream.is_open() || !getline(stream, output)) {
        ASSERT_NO_FATAL_FAILURE("File could not open");
        return;
    }
    stream.close();
    remove("output.txt");
    std::size_t pos = output.find(")");
    std::string str = output.substr(pos + 2);
    ASSERT_STREQ("[Info] Info message in test::switchModeTestInverse", str.c_str());
}

TEST(LoggerTests, setFlags)
{
    Debug::Logger *log = Debug::Logger::getInstance();
    std::string output;
    testing::internal::CaptureStdout();

    log->setFlags(Debug::Flags::info_off);
    log->generateDebugMessage(Debug::INFO, "Info message", "test::switchModeTest");
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    output = testing::internal::GetCapturedStdout();
    ASSERT_STREQ("", output.c_str());
}

TEST(LoggerTests, logOff)
{
    Debug::Logger *log = Debug::Logger::getInstance(Debug::OFF);
    std::string output;
    testing::internal::CaptureStdout();

    log->generateDebugMessage(Debug::INFO, "Info message", "test::switchModeTest");
    log->generateDebugMessage(Debug::INFO, "Info message", "test::switchModeTest");
    log->generateDebugMessage(Debug::INFO, "Info message", "test::switchModeTest");
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    output = testing::internal::GetCapturedStdout();
    ASSERT_STREQ("", output.c_str());
}