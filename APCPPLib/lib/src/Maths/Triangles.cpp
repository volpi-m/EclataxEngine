//
// Created by tabis on 09/10/2019.
//

#include "Triangles.hpp"

bool Maths::is_triangle_rectangle(const std::tuple<float, float, float> &&sizes, const float precision)
{
    // Getting the maximum index value from all sides
    float max = Utils::max_tuple_value(sizes);

    // Sum of both smallest sides
    float result = pow(std::get<0>(sizes), 2) + pow(std::get<1>(sizes), 2) + pow(std::get<2>(sizes), 2) - pow(max, 2);
    
    return (pow(max, 2) - result) < precision;
}