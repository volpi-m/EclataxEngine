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

#include "Entity.hpp"

namespace Game {

    /// \class IEnnemy
    /// \brief Interface for creating ennemy as shared librairies
    class IEnnemy {

        public:
            virtual ECS::Entity *createEntity() = 0;
    };
}