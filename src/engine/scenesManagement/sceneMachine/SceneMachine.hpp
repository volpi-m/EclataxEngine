/*
** EPITECH PROJECT, 2019
** SceneMachine.hpp
** File description:
** SceneMachine class
*/

/// \file SceneMachine.hpp
/// \author Lucas T.
/// \brief Header file for the SceneMachine class

#pragma once

#include <stack>
#include <string>
#include <chrono>
#include <thread>

#include "IScene.hpp"
#include "Rfc.hpp"

/// \namespace Scenes
/// \brief Used for the all Scenes subsclasses
namespace Module {

    /// \class SceneMachine
    /// \brief Create a singleton instance that will stack scenes and manipulate them
    class SceneMachine {
        public:
            /// \brief constructor
            /// Initialize SceneMachine class
            SceneMachine();
            
            /// \brief destructor
            /// Destroy SceneMachine class
            ~SceneMachine();

            /// \param scene : The scene to push
            /// \brief Push a scene pointer into the stack
            void push(std::shared_ptr<Scenes::IScene> &scene);

            /// \brief Destroy the scene on top of the stack
            void pop();

            /// \param name : Last scene to destroy
            /// \brief Destroy all scenes unit the current scene corespond to the name parameter
            void pop(const std::string &name);

            /// \param name : Last scene to destroy
            /// \brief Destroy all scenes unit the current scene corespond to the name parameter
            void pop(const char *name);

            /// \param scene : The scene to replace
            /// \brief Swap the current scene with the scene passed as parameter
            void swap(std::shared_ptr<Scenes::IScene> &scene);

            /// \return the size of the stack
            /// \brief get the size of the stack
            size_t size() const;

            /// \return the name of the current scene
            /// \brief get the name of the current scene
            std::string name() const;

            /// \return a bool, true if the scene is to be poped, false otherwise
            /// \brief check if the current scene needs to be destroyed
            bool isToPop() const;

            /// \return a bool, true if the scene is to be swaped, false otherwise
            /// \brief check if the current scene needs to be swaped
            bool isToSwap() const;

            /// \brief starts the machine
            Scenes::IScene *run();

            /// \brief get the entity stack to send to clients
            /// \return a reference to the stack
            std::stack<Network::Entity> &getCurrentSceneEntityStack();

            /// \param event : queue of current events
            /// \brief transfert events from hub to scene
            void sendEventsToCurrentScene(std::queue<std::pair<int, size_t>> &events);

            /// \brief clear all scene in th stack
            void clear();

            /// \brief remove elements of top scene
            void remove();



        private:
            /*! the stack of scenes */
            std::stack<std::shared_ptr<Scenes::IScene>> _scenes;
    };
}