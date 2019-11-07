/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Game Engine methods
*/

#pragma once

namespace Game {

    class GameEngine {
    public:
        GameEngine();
        ~GameEngine();

        bool isInitialised();
        // EntityComponentSystem &EntityComponentSystem() {return _ecs;};
        // LibLoader &LibLoader() {return _libLoader;};
        // SceneManager &SceneManager() {return _sceneManager;};
    private:
        void init();

        bool _initialised;
        // EntityComponentSystem _ecs;
        // LibLoader _libLoader;
        // SceneManager _sceneManager;
    };
}
