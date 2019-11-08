/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Game Engine methods
*/

#include "SceneMachine.hpp"
#include "ECS.hpp"

#pragma once

namespace Game {

    class GameEngine {
    public:
        GameEngine();
        ~GameEngine();

        bool isInitialised() const;
        Module::EntityComponentSystem &ECS();
        // LibLoader &LibLoader() {return _libLoader;};
        Module::SceneMachine &SceneManager();
    private:
        void init();

        bool _initialised;
        Module::EntityComponentSystem _ecs;
        // LibLoader _libLoader;
        Module::SceneMachine _sceneMachine;
    };
}
