//
// Created by tabis on 10/10/2019.
//

#include "Logger.hpp"
#include <gtest/gtest.h>

TEST(LoggerTests, debugMessageOnStdout)
{
    testing::internal::CaptureStdout();
    std::string output;

    Debug::Logger::printDebug(Debug::DEBUG, "debug message", "test::debugMessageOnStdout");

    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    output = testing::internal::GetCapturedStdout();
    std::size_t pos = output.find(")");
    std::string str = output.substr(pos + 2);
    ASSERT_STREQ("\033[m[Debug]\033[0;36m debug message\033[m in \033[0;35mtest::debugMessageOnStdout\033[m\n", str.c_str());
}

TEST(LoggerTests, debugMessageInFile)
{
    std::string output;

    Debug::Logger::setFileOutput("output.txt");
    Debug::Logger::switchMode(Debug::FILE);
    Debug::Logger::printDebug(Debug::INFO, "Info message", "test::debugMessageInFile");

    std::this_thread::sleep_for(std::chrono::milliseconds(5));

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
    std::string output;
    testing::internal::CaptureStdout();

    Debug::Logger::setFileOutput("output.txt");
    Debug::Logger::switchMode(Debug::STANDARD);
    Debug::Logger::printDebug(Debug::INFO, "Info message", "test::switchModeTest");

    std::this_thread::sleep_for(std::chrono::milliseconds(5));

    output = testing::internal::GetCapturedStdout();
    std::size_t pos = output.find(")");
    std::string str = output.substr(pos + 2);
    ASSERT_STREQ("\033[m\033[0;32m[Info]\033[0;36m Info message\033[m in \033[0;35mtest::switchModeTest\033[m\n", str.c_str());
}

TEST(LoggerTests, switchModeTestInverse)
{
    std::string output;

    Debug::Logger::switchMode(Debug::FILE);
    Debug::Logger::printDebug(Debug::INFO, "Info message", "test::switchModeTestInverse");

    std::this_thread::sleep_for(std::chrono::milliseconds(5));

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
    std::string output;
    testing::internal::CaptureStdout();

    Debug::Logger::setFlags(Debug::Flags::info_off);
    Debug::Logger::printDebug(Debug::INFO, "Info message", "test::switchModeTest");
    
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    
    output = testing::internal::GetCapturedStdout();
    ASSERT_STREQ("", output.c_str());
}

TEST(LoggerTests, logOff)
{
    std::string output;
    testing::internal::CaptureStdout();

    Debug::Logger::setFlags(Debug::OFF);
    Debug::Logger::printDebug(Debug::INFO, "Info message", "test::switchModeTest");
    Debug::Logger::printDebug(Debug::ERROR, "Error message", "test::switchModeTest");
    Debug::Logger::printDebug(Debug::DEBUG, "Debug message", "test::switchModeTest");

    std::this_thread::sleep_for(std::chrono::milliseconds(5));

    output = testing::internal::GetCapturedStdout();
    ASSERT_STREQ("", output.c_str());
}