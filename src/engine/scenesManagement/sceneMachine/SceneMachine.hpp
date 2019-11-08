/*
** EPITECH PROJECT, 2019
** SceneMachine.hpp
** File description:
** SceneMachine class
*/

#pragma once

#include <stack>
#include <string>
#include <chrono>
#include <thread>

#include "IScene.hpp"

namespace indie {
    class SceneMachine {
        public:
            static SceneMachine *getInstance();
            void push(IScene *scene);
            void pop();
            void pop(const std::string &name);
            void swap(indie::IScene *scene);

            // Getter
            size_t size() const;
            std::string getSceneName() const;
            bool isToPop() const;
            void run();
        private:
            SceneMachine() = default;
            std::stack<IScene *> _scenes;
    };
}