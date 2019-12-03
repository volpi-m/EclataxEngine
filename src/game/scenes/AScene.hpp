/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** Abstract class for scene
*/

/// \file Ascene.hpp
/// \author Arthur L.
/// \brief Abstract scene class declaration

#pragma once

#include "Animation2DComponent.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "IScene.hpp"
#include "Logger.hpp"

/// \namespace Scenes
/// \brief Used for all scenes
namespace Scenes
{

    enum Event { UP = 1, DOWN = 2, LEFT = 4, RIGHT = 8, ENTER = 16, SPACE = 32, ESCAPE = 64};

    /// \class AScene
    /// \brief Abstract class for each scene, add some other functions plus useful attributes
    class AScene : public IScene
    {
        public:
            /// \param name : the new name of the current scene
            /// \param ECS : ECS instance to pass to the scene
            /// \param players : number of players
            /// \brief scene constructor
            AScene(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS, int players);

            /// \param name : the new name of the current scene
            /// \param ECS : ECS instance to pass to the scene
            /// \param players : number of players
            /// \brief scene constructor
            AScene(const char *name, std::shared_ptr<Module::EntityComponentSystem> &ECS, int players);

            /// \param players : number of players
            /// \param name : the new name of the current scene
            /// \brief scene constructor
            AScene(int players, const std::string &name = default_tag);

            /// \param players : number of players
            /// \param name : the new name of the current scene
            /// \brief scene constructor
            AScene(int players, const char *name = default_tag);

            /// \brief default scene destructor
            ~AScene() override = default;

            /// \return the name of the current scene
            /// \brief get the name of the current scene
            std::string name() const override;

            /// \param name : the new name of the current scene
            /// \brief change the name of the scene
            void setName(const std::string &name);

            /// \return a bool if the scene needs to be poped when destroyed
            /// \brief scene deletion characteristic
            bool isToPop() const override;

            /// \return a bool if the scene needs to be swaped when destroyed
            /// \brief scene deletion characteristic
            bool isToSwap() const override;

            /// \param ECS : The entity compponent system to pass to the scene
            /// \brief set an instance of the ECS inside the scene object
            void setECSInstance(std::shared_ptr<Module::EntityComponentSystem> &ECS) override;

            /// \return a bool representing the state of the scene
            /// \brief run the scenes logic
            virtual IScene *run() override = 0;

            /// \param bool : the visible state of the scene
            /// \brief set visible state of the scene
            virtual void setVisible(bool state) override = 0;

            /// \param bool : if the scene as to be poped
            /// \brief set the pop state of the scene
            void setPop(bool pop) override;

            /// \brief remove all the entities of the scene
            virtual void remove() override = 0;

            /// \brief getting the entity stack of the scene
            /// \return a stack of entities that will be sent to the client
            std::stack<Network::Entity> &entityStack() override;

            /// \param entity : The entity that will be pushed onto the stack
            /// \brief push an entity to the stack of the scene
            void pushEntityStack(std::shared_ptr<ECS::Entity> &entity, std::size_t id) override;

            /// \param events : queue of all events.
            /// The first element of pair is the number of the player that did the event
            /// The second element of pair is the event
            /// \brief push an entity to the stack of the scene
            virtual void handleEvent(std::queue<std::pair<int, size_t>> events) = 0;

        protected:
            /*! name of the scene */
            std::string _name;
            /*! ECS instance */
            std::shared_ptr<Module::EntityComponentSystem> _ECS;
            /*! pop characteristic */
            bool _pop;
            /*! swap characteristic */
            bool _swap;
            /*! stack of entity */
            std::stack<Network::Entity> _stack;
            /*! number of players */
            int _players;
    };
}