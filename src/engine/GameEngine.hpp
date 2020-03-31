/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Game Engine methods
*/

/// \file GameEngine.hpp
/// \author Lucas T.
/// \brief Header file for the GameEngine class

#include "SceneStateMachine.hpp"
#include "LibraryLoader.hpp"
#include "ECS.hpp"

#pragma once

/// \namespace Game
/// \brief Used for the game engine components
namespace Game
{

    /// \class GameEngine
    /// \brief GameEngine class, get all modules of the engine
    class GameEngine
    {
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

        /// \brief get the LibraryLoader instance
        /// \return a shared poiner of the LibraryLoader module
        std::shared_ptr<Module::LibraryLoader> &LibraryLoader();

        /// \brief get the SceneStateMachine instance
        /// \return a shared poiner of the SceneStateMachine module
        std::shared_ptr<Module::SceneStateMachine> &SceneStateMachine();
    private:
        void init();

        /*! ECS instance */
        std::shared_ptr<Module::EntityComponentSystem> _ecs;
        /*! LibraryLoader instance */
        std::shared_ptr<Module::LibraryLoader> _libraryLoader;
        /*! SceneStateMachine instance */
        std::shared_ptr<Module::SceneStateMachine> _sceneStateMachine;
        /*! iniialisation value */
        bool _initialised;
    };
}
