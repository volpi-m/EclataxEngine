/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component interface
*/

#pragma once

#include <cstdint>

#include "IComponent.hpp"

namespace ECS {

    struct Transform : public IComponent {
        std::size_t _x;
        std::size_t _y;
        std::size_t _z;
    };
}
