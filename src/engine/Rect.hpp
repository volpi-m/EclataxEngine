/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Rect struct
*/

/// \file Rect.hpp
/// \author Lucas T.
/// \brief Header file for the Rect struct

#pragma once

/// \namespace Game
/// \brief Used for the game engine components
namespace Game {

    /// \class Rect
    /// \brief Rect class, data of a rectangle
    struct Rect {

        /// \brief constructor
        Rect() : top(0), left(0), width(0), height(0) {}

        /// \brief constructor
        Rect(float _top, float _left, float _width, float _height) : top(_top), left(_left), width(_width), height(_height) {}

        /*! top of the rectangle attribute */
        float top;
        /*! left pos of the rectangle attribute */
        float left;
        /*! width of the rectangle attribute */
        float width;
        /*! height of the rectangle attribute */
        float height;
    };
}
