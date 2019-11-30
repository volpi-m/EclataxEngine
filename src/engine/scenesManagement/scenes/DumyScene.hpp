//
// EPITECH PROJECT, 2019
// DumyScene.hpp
// File description:
// DumyScene class declaration
//

/// \file DumyScene.hpp
/// \author Lucas T.
/// \brief DumyScene class declaration

#pragma once

#include <string>
#include <memory>
#include <tuple>

#include "Animation2DComponent.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "MovementSystem.hpp"
#include "SpawnerSystem.hpp"
#include "IASystem.hpp"
#include "IScene.hpp"
#include "Logger.hpp"

/// \namespace Scenes
/// \brief Used for all scenes components
namespace Scenes {

    /// \class DumyScene
    /// \brief DumyScene class
    class DumyScene : public IScene {
        public:
            /// \param name : the new name of the current scene
            /// \param ECS : ECS instance to pass to the scene
            /// \brief scene constructor
            DumyScene(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS);

            /// \param name : the new name of the current scene
            /// \param ECS : ECS instance to pass to the scene
            /// \brief scene constructor
            DumyScene(const char *name, std::shared_ptr<Module::EntityComponentSystem> &ECS);

            /// \param name : the new name of the current scene
            /// \brief scene constructor
            DumyScene(const std::string &name = default_tag);

            /// \param name : the new name of the current scene
            /// \brief scene constructor
            DumyScene(const char *name = default_tag);

            /// \brief default scene destructor
            ~DumyScene() override = default;

            /// \param name : the new name of the current scene
            /// \brief change the name of the scene
            void setName(const std::string &name) override;

            /// \return the name of the current scene
            /// \brief get the name of the current scene
            std::string name() const override;

            /// \return a scene representing the state of the scene
            /// \brief run the scenes logic
            IScene *run() override;
            
            /// \return a bool if the scene needs to be poped when destroyed
            /// \brief scene deletion characteristic
            bool isToPop() const override;

            /// \return a bool if the scene needs to be swaped when destroyed
            /// \brief scene deletion characteristic
            bool isToSwap() const override;

            /// \param bool : the visible state of the scene
            /// \brief set visible state of the scene
            void setVisible(bool state) override;

            /// \param bool : if the scene as to be poped
            /// \brief set the pop state of the scene
            void setPop(bool pop) override;

            /// \brief remove all the entities of the scene
            void remove() override;

            /// \param ECS : The entity compponent system to pass to the scene
            /// \brief set an instance of the ECS inside the scene object
            void setECSInstance(std::shared_ptr<Module::EntityComponentSystem> &ECS) override;

            /// \brief getting the entity stack of the scene
            /// \return a stack of entities that will be sent to the client
            std::stack<Network::Entity> &entityStack() override;

            /// \brief handle events
            void handleEvent(std::queue<std::pair<int, size_t>> &events);

        private:
            /// \param entity : The entity that will be pushed onto the stack
            /// \param id : id of the entity
            /// \brief push an entity to the stack of the scene
            void pushEntityStack(std::shared_ptr<ECS::Entity> &entity, std::size_t id) override;

            /*! name of the scene */
            std::string _name;
            /*! ECS instance */
            std::shared_ptr<Module::EntityComponentSystem> _ECS;
            /*! scene entities */
            std::vector<unsigned long long> _ids;
            /*! pop characteristic */
            bool _pop;
            /*! swap characteristic */
            bool _swap;
            /*! stack of entity */
            std::stack<Network::Entity> _stack;
    };
}