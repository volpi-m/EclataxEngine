/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Game Engine methods
*/

/// \file GameEngine.hpp
/// \author Lucas T.
/// \brief Header file for the GameEngine class

#include "SceneMachine.hpp"
#include "ECS.hpp"

#pragma once

/// \namespace Game
/// \brief Used for the game engine components
namespace Game {

    /// \class GameEngine
    /// \brief GameEngine class, get all modules of the engine
    class GameEngine {
    public:
        /// \brief constructor
        /// Initialize GameEngine class
        GameEngine();

        /// \brief destructor
        /// Destroy GameEngine class
        ~GameEngine();

        /// \brief checks if all modules are initiated correctly
        /// \return a bool, true if all modules are initiated, false otherwise
        bool isInitialised() const;

        /// \brief get the ECS instance
        /// \return a shared poiner of the ECS module
        std::shared_ptr<Module::EntityComponentSystem> &ECS();

        /// \brief get the LibLoader instance
        /// \return a shared poiner of the LibLoader module
        // LibLoader &LibLoader() {return _libLoader;};

        /// \brief get the SceneMachine instance
        /// \return a shared poiner of the SceneMachine module
        std::shared_ptr<Module::SceneMachine> &SceneMachine();
    private:
        void init();

        /*! ECS instance */
        std::shared_ptr<Module::EntityComponentSystem> _ecs;
        /*! LibLoader instance */
        // LibLoader _libLoader;
        /*! SceneMachine instance */
        std::shared_ptr<Module::SceneMachine> _sceneMachine;
        /*! iniialisation value */
        bool _initialised;
    };
}
