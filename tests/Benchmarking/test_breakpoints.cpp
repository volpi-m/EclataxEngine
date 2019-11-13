//
// Created by tabis on 10/10/2019.
//

#include "Breakpoint.hpp"
#include <gtest/gtest.h>

TEST(BreakpointTest, simpleBreakpoint)
{
    testing::internal::CaptureStdout();
    std::string output;

    {
        Debug::Breakpoint("Test", "BreakpointTest");
    }
    output = testing::internal::GetCapturedStdout();
    std::size_t pos = output.find(")");
    std::string str = output.substr(pos + 2, std::string("\x1B[m[\x1B[0;41m0\x1B[m][Breakpoint] Operation \x1B[0;36mTest\x1B[m in \x1B[0;35mBreakpointTest\x1B[m lasted for").size());
    ASSERT_STREQ("\x1B[m[\x1B[0;41m0\x1B[m][Breakpoint] Operation \x1B[0;36mTest\x1B[m in \x1B[0;35mBreakpointTest\x1B[m lasted for", str.c_str());
}