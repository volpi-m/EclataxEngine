//
// Created by tabis on 10/10/2019.
//

#include "Exception.hpp"
#include <gtest/gtest.h>

TEST(ExceptionTests, normalThrow)
{
    testing::internal::CaptureStderr();
    std::string output;

    try {
        throw Debug::Exception("An error occurred", "Somewhere");
    } catch (const Debug::Exception &exception) {
        exception.debugErrorMessage();
    }
    output = testing::internal::GetCapturedStderr();
    ASSERT_STREQ("\x1B[0;31m[Exception] \x1B[0;35mAn error occurred\x1B[m in method \x1B[0;34mSomewhere\n", output.c_str());
}

TEST(ExceptionTests, stringThrow)
{
    testing::internal::CaptureStderr();
    std::string output;

    try {
        throw Debug::Exception(std::string("An error occurred"), std::string("Somewhere"));
    } catch (const Debug::Exception &exception) {
        exception.debugErrorMessage();
    }
    output = testing::internal::GetCapturedStderr();
    ASSERT_STREQ("\x1B[0;31m[Exception] \x1B[0;35mAn error occurred\x1B[m in method \x1B[0;34mSomewhere\n", output.c_str());
}