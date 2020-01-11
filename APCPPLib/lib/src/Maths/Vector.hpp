//
// Created by tabis on 09/10/2019.
//

#pragma once

#include <iostream>

/// \namespace Maths
/// \brief math namespace
namespace Maths {

    /// \class Vector3
    /// \brief Vector class that stores three coordinates
    template<typename T>
    struct Vector3 {
        /// \brief Ctor
        /// Construct the Vector3 class
        Vector3() : x(0), y(0), z(0) {}
        /// \brief Ctor
        /// Construct the Vector3 class
        /// \param value : value of all fields
        Vector3(T value) : x(value), y(value), z(value) {}
        /// \brief Ctor
        /// Construct the Vector3 class
        /// \param xx : x field value
        /// \param yy : y field value
        /// \param zz : z field value
        Vector3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}
        /// \brief Dtor
        /// Destroy the Vector2 class
        ~Vector3() = default;

        T x, y, z;

    /// \class Vector2
    /// \brief Vector class that stores two coordinates
    template<typename T>
    struct Vector2 {
        /// \brief Ctor
        /// Construct the Vector2 class
        Vector2() : x(0), y(0) {}
        /// \brief Ctor
        /// Construct the Vector2 class
        /// \param value : value of all fields
        Vector2(T value) : x(value), y(value) {}
        /// \brief Ctor
        /// Construct the Vector2 class
        /// \param xx : x field value
        /// \param yy : y field value
        Vector2(T xx, T yy, T zz) : x(xx), y(yy) {}
        /// \brief Dtor
        /// Destroy the Vector2 class
        ~Vector2() = default;

        T x, y;
    };
}