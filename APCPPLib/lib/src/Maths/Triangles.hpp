//
// Created by tabis on 09/10/2019.
//

#pragma once

#include <algorithm>
#include <iostream>
#include <cmath>

#include "Tuples.hpp"

/// \namespace Maths.
/// \brief math namespace.
namespace Maths
{
    /// \brief calculate the hypotenuse of a triangle.
    /// \param far : far corner.
    /// \param near : near corner.
    /// \return the hypotenuse length.
    template<typename T>
    T calculate_hypotenuse(T far, T near)
    {
        return std::sqrt((far * far) + (near * near));
    }

    /// \brief calculate if a triangle is rectangle.
    /// \param sizes : sides sizes of a triangle.
    /// \param precision : float precision.
    /// \return true if the triangle is rectangle, false otherwise.
    bool is_triangle_rectangle(const std::tuple<float, float, float> &&sizes, const float precision);
}