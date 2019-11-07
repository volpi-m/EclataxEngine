/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Entity class declaration
*/

#pragma once

#include <unordered_map>
#include <iostream>
#include <memory>
#include <vector>

#include "IComponent.hpp"
#include "Entity.hpp"

namespace ECS {

    class ISystem {
        public:
            virtual void update(std::unordered_map<unsigned long long, std::shared_ptr<Entity>> &entities) = 0;
    };
}