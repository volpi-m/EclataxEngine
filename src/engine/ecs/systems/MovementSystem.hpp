/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** MovementSystem class declaration
*/

#pragma once

#include <unordered_map>
#include <iostream>
#include <memory>
#include <vector>

#include "ISystem.hpp"
#include "Entity.hpp"
#include "TransformComponent.hpp"

namespace ECS {

    class MovementSystem : public ISystem {
        public:
            void update(std::unordered_map<unsigned long long, std::shared_ptr<Entity>> &entities) override;
    };
}