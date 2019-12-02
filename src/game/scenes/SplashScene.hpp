/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** splash screen
*/

/// \file SplashScene.hpp
/// \author Arthur L.
/// \brief SplashScene class declaration

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
    class SplashScene : public AScene {

        public:
            /// \param name : the new name of the current scene
            /// \param ECS : ECS instance to pass to the scene
            /// \param player : number of players
            /// \brief scene constructor
            SplashScene(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS, int player);

            /// \param name : the new name of the current scene
            /// \param ECS : ECS instance to pass to the scene
            /// \param player : number of players
            /// \brief scene constructor
            SplashScene(const char *name, std::shared_ptr<Module::EntityComponentSystem> &ECS, int player);

            /// \param player : number of players
            /// \param name : the new name of the current scene
            /// \brief scene constructor
            SplashScene(int player, const std::string &name = default_tag);

            /// \param player : number of players
            /// \param name : the new name of the current scene
            /// \brief scene constructor
            SplashScene(int player, const char *name = default_tag);

            /// \brief default scene destructor
            ~SplashScene() override = default;

            /// \return a bool representing the state of the scene
            /// \brief run the scenes logic
            IScene *run() override;

            /// \param bool : the visible state of the scene
            /// \brief set visible state of the scene
            void setVisible(bool state) override;

            /// \brief remove all the entities of the scene
            void remove() override;

            /// \brief handle events
            void handleEvent(std::queue<std::pair<int, size_t>> events);


        private:
            /*! scene entities */
            std::vector<unsigned long long> _ids;

            /// \brief method for initialize all scene components
            void initComponents();
    };
}