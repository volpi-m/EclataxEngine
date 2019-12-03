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
#include <functional>

#include "AScene.hpp"
#include "HealthManipulatorSystem.hpp"
#include "TransformComponent.hpp"
#include "AnimationSystem.hpp"
#include "CollisionSystem.hpp"
#include "MovementSystem.hpp"
#include "LifeSpanSystem.hpp"
#include "SpawnerSystem.hpp"
#include "Level2Scene.hpp"
#include "IASystem.hpp"

#include "Fleet.hpp"

/// \namespace Scenes
/// \brief Used for all scenes
namespace Scenes {

    /// \class Level1Scene
    /// \brief Level2Scene class
    class Level1Scene : public AScene {

        public:
            /// \param name : the new name of the current scene
            /// \param ECS : ECS instance to pass to the scene
            /// \param players : number of players
            /// \brief scene constructor
            Level1Scene(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS, int player);

            /// \param name : the new name of the current scene
            /// \param ECS : ECS instance to pass to the scene
            /// \param players : number of players
            /// \brief scene constructor
            Level1Scene(const char *name, std::shared_ptr<Module::EntityComponentSystem> &ECS, int player);

            /// \param name : the new name of the current scene
            /// \param players : number of players
            /// \brief scene constructor
            Level1Scene(int player, const std::string &name = default_tag);

            /// \param name : the new name of the current scene
            /// \param players : number of players
            /// \brief scene constructor
            Level1Scene(int player, const char *name = default_tag);

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
            void handleEvent(std::queue<std::pair<int, size_t>> events);


        private:

            /// \brief check if players are still alive
            /// \return a boolean set to true if a player is still alive, false otherwise
            bool alivePlayers();

            /// \brief get all players current speeds
            /// \param speeds : array of speeds
            /// \param movementSystem : the system that will get the speeds
            void getPlayersSpeed(float *speeds, ECS::System::MovementSystem *movementSystem);

            /// \brief get all players current speeds
            /// \param first : an entity
            /// \param second : another entity
            /// \param collisionSystem : the system that will check colision
            void checkCollisionTags(std::shared_ptr<ECS::Entity> &first, std::shared_ptr<ECS::Entity> &second,  ECS::System::CollisionSystem *collisionSystem);

            /// \brief get all players current speeds
            /// \param entity : player to compute
            /// \param lastShot : last time the player shot
            void computeShots(std::shared_ptr<ECS::Entity> &entity, std::chrono::high_resolution_clock::time_point &lastShot);

            /// \brief change the waves
            void changeWave();

            bool checkPlayer(std::pair<int, std::size_t> &key);

            /// \brief method for initialize all scene components
            void initComponents();

            std::unordered_map<int, std::size_t> _playersIds;

            /*! scene entities */
            std::vector<unsigned long long> _ids;

            /*! maximum waves */
            int _MaxWaves = 4;
            int _currentWave = 0;

            /*! waves instanciation */
            std::vector<std::function<void(Level1Scene &)>> _waves;

            /*! waves */
            void waveOne();
            void waveTwo();
            void waveThree();
            void waveFour();
            void waveFive();
    };
}