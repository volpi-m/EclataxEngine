/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component interface
*/

#pragma once

#include <string>

#include "IComponent.hpp"

namespace ECS {

    struct Audio : public IComponent {
        std::string _file;
    };
}
