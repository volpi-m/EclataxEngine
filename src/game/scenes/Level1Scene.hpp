/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** Level1Scene screen
*/

/// \file Level1Scene.hpp
/// \author Lucsa T.
/// \brief Level1Scene class declaration

#pragma once

#include <iostream>


#include "AScene.hpp"
#include "TransformComponent.hpp"
#include "AnimationSystem.hpp"
#include "MovementSystem.hpp"
#include "LifeSpanSystem.hpp"
#include "SpawnerSystem.hpp"
#include "IASystem.hpp"

/// \namespace Scenes
/// \brief Used for all scenes
namespace Scenes {

    /// \class SplashScene
    /// \brief SplashScene class
    class Level1Scene : public AScene {

        public:
            /// \param name : the new name of the current scene
            /// \param ECS : ECS instance to pass to the scene
            /// \brief scene constructor
            Level1Scene(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS);

            /// \param name : the new name of the current scene
            /// \param ECS : ECS instance to pass to the scene
            /// \brief scene constructor
            Level1Scene(const char *name, std::shared_ptr<Module::EntityComponentSystem> &ECS);

            /// \param name : the new name of the current scene
            /// \brief scene constructor
            Level1Scene(const std::string &name = default_tag);

            /// \param name : the new name of the current scene
            /// \brief scene constructor
            Level1Scene(const char *name = default_tag);

            /// \brief default scene destructor
            ~Level1Scene() override = default;

            /// \return a bool representing the state of the scene
            /// \brief run the scenes logic
            IScene *run() override;

            /// \param bool : the visible state of the scene
            /// \brief set visible state of the scene
            void setVisible(bool state) override;

            /// \brief remove all the entities of the scene
            void remove() override;

            /// \brief handle events
            void handleEvent(std::queue<std::pair<int, size_t>> &events);


        private:
            /*! scene entities */
            std::vector<unsigned long long> _ids;

            /// \brief method for initialize all scene components
            void initComponents();
    };
}