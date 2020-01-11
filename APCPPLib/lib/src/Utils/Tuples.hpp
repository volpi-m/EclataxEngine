//
// Created by tabis on 09/10/2019.
//

#pragma once

#include <iostream>
#include <tuple>

/// \namespace Utils
/// \brief utils methods namespace
namespace Utils
{

    /// \brief A compile time recursive function that calculate the maximum value of a tuple.
    /// \param tuple : the tuple that we want to iterate through.
    /// \return A type specified by the variadic template.
    template<size_t I = 0, typename ... T>
    auto max_tuple_value(const std::tuple<T ...> &tuple)
    {
        // Checks if the current value is greater than the rest of all values.
        if constexpr(I + 1 != sizeof ...(T))
        {
            auto current = std::get<I>(tuple);
            auto next = max_tuple_value<I + 1>(tuple);

            return current > next ? current : next;
        }

        // Where at the end of the tuple, returning the last element.
        return std::get<I>(tuple);
    }

    /// \brief A compile time recursive function that calculate the sum elements of a tuple.
    /// \param tuple : the tuple that we want to iterate through.
    /// \return A type specified by the variadic template.
    template<size_t I = 0, typename ... T>
    auto tuple_sum(const std::tuple<T ...> &tuple)
    {
        // Adding the current value to the next.
        if constexpr(I + 1 != sizeof ...(T))
            return std::get<I>(tuple) + tuple_sum<I + 1>(tuple);

        // Where at the end of the tuple, returning the last element.
        return std::get<I>(tuple);
    }
}