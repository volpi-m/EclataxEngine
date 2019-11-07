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

namespace ECS {

    class Entity {
        public:
            Entity() = default;
            ~Entity() = default;

            void update();
            void addChild(Entity &child);
            std::string &getTag();
            bool hasComponent(unsigned char flag);
        private:
            void deleteEntity();

            std::string _tag;
            std::unordered_map<unsigned char, std::unique_ptr<IComponent>> _components;
            std::vector<std::shared_ptr<Entity>> _children;
            bool _deleted;
    };
}