/*
** EPITECH PROJECT, 2019
** IScene.hpp
** File description:
** IScene class interface
*/

#pragma once

#include <stack>
#include <cstring>

#include "ECS.hpp"
#include "Rfc.hpp"

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

            /// \brief getting the entity stack of the scene
            /// \return a stack of entities that will be sent to the client
            virtual std::stack<Network::Entity> &entityStack() = 0;

            /// \param entity : The entity that will be pushed onto the stack
            /// \param id : the id of the entity
            /// \brief push an entity to the stack of the scene
            virtual void pushEntityStack(std::shared_ptr<ECS::Entity> &entity, std::size_t id) = 0;

            /// \param event : stack of all event
            /// Int is the number of the player
            /// size_t is the event
            /// \brief manage all event in the scene
            virtual void handleEvent(std::queue<std::pair<int, size_t>> event) = 0;
    };
}