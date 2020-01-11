//
// Created by tabis on 10/10/2019.
//

#include "Triangles.hpp"
#include <gtest/gtest.h>

TEST(FormulaTests, pythagore)
{
    ASSERT_EQ(Maths::calculate_hypotenuse<int>(3, 5), 5);
    ASSERT_EQ((int)Maths::calculate_hypotenuse<float>(10, 10), 14);
}

TEST(FormulaTests, is_triangle_rectangle)
{
    ASSERT_EQ(Maths::is_triangle_rectangle(std::make_tuple(9.0f, 7.0f, 4.0f), 0.0001), false);
    ASSERT_EQ(Maths::is_triangle_rectangle(std::make_tuple(3.0f, 5.0f, 5.83095f), 0.000001), true);
}