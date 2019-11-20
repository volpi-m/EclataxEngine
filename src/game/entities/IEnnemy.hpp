/*
** EPITECH PROJECT, 2019
** rType
** File description:
** Interface for ennemy
*/

/// \file IEnnemy.hpp
/// \author Arthur L.
/// \brief Interface for implementing ennemies

#pragma once

#include <iostream>

/// \namespace Game
/// \brief Used for the game part classes
namespace Game {

    /// \class IEnnemy
    /// \brief Interface for creating ennemy as shared librairies
    class IEnnemy {

        public:
            /// \brief constructor
            /// Initialize IEnnemy class
            IEnnemy();

            virtual void initComponent() = 0;
            // virtual void move() = 0;
            // virtual void shot() = 0;
            // virtual void kill() = 0;
    };
}