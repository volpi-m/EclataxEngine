//
// Created by tabis on 10/10/2019.
//

#include "Tuples.hpp"
#include <gtest/gtest.h>

TEST(TuplesTests, One)
{
    ASSERT_EQ(Utils::max_tuple_value(std::make_tuple(1)), 1);
}

TEST(TuplesTests, MutipleInt)
{
    ASSERT_EQ(Utils::max_tuple_value(std::make_tuple(150, 200, 7, 89)), 200);
}

TEST(TuplesTests, MutipleFloats)
{
    ASSERT_EQ(Utils::max_tuple_value(std::make_tuple(55.0f, 21.0f, 1.0f, 360.5f)), 360.5f);
    ASSERT_EQ(Utils::max_tuple_value(std::make_tuple(5.32f, 21.513f, 21.512f)), 21.513f);
}

TEST(TuplesTests, addMutipleInt)
{
    ASSERT_EQ(Utils::tuple_sum(std::make_tuple(104, 2, 10, 1000)), 1116);
}

TEST(TuplesTests, addMutipleFloats)
{
    ASSERT_EQ(Utils::tuple_sum(std::make_tuple(55.0f, 21.0f, 1.0f, 360.5f)), 437.5f);
}

TEST(TuplesTests, sumLvalue)
{
    std::tuple<int, int, int, int, int, int> tpl(1, 10, 100, 1000, 10000, 100000);
 
    ASSERT_EQ(Utils::tuple_sum(tpl), 111111);
}

TEST(TuplesTests, maxLvalue)
{
    std::tuple<int, int, int, int, int, int> tpl(1, 10, 100, 1000, 10000, 100000);
 
    ASSERT_EQ(Utils::max_tuple_value(tpl), 100000);
}