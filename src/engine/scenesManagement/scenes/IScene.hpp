/*
** EPITECH PROJECT, 2019
** IScene.hpp
** File description:
** IScene class interface
*/

#include "ECS.hpp"

#pragma once

/// \namespace Scenes
/// \brief Used for all scenes components
namespace Scenes {

    /// \class IScene
    /// \brief Scene interface
    class IScene {
        public:
            /// \brief destructor
            /// Destroy IScene class
            virtual ~IScene() = default;

            /// \param name : the new name of the current scene
            /// \brief change the name of the scene
            virtual void setName(const std::string &name) = 0;

            /// \return the name of the current scene
            /// \brief get the name of the current scene
            virtual std::string name() const = 0;

            /// \return a scene representing the state of the scene
            /// \brief run the scenes logic
            virtual IScene *run() = 0;

            /// \return a bool if the scene needs to be poped when destroyed
            /// \brief scene deletion characteristic
            virtual bool isToPop() const = 0;

            /// \return a bool if the scene needs to be swaped when destroyed
            /// \brief scene deletion characteristic
            virtual bool isToSwap() const = 0;

            /// \param bool : the visible state of the scene
            /// \brief set visible state of the scene
            virtual void setVisible(bool b) = 0;

            /// \param bool : if the scene as to be poped
            /// \brief set the pop state of the scene
            virtual void setPop(bool pop) = 0;
            
            /// \brief remove all the entities of the scene
            virtual void remove() = 0;

            /// \param ECS : The entity compponent system to pass to the scene
            /// \brief set an instance of the ECS inside the scene object
            virtual void setECSInstance(std::shared_ptr<Module::EntityComponentSystem> &ECS) = 0;
    };
}