/*
** EPITECH PROJECT, 2019
** rType
** File description:
** Hub loading scene declaration
*/

#pragma once

#include "AScene.hpp"
#include "TextComponent.hpp"
#include "TextSystem.hpp"
/// \namespace Scenes
/// \brief Used for all scenes
namespace Scenes {

    /// \def path for ship sprite
    constexpr const auto SHIP_PATH = "lib/ship.so";

    struct HubPlayer
    {
        HubPlayer(bool state, unsigned long long text) : state(state), text(text) {};
        bool state;
        unsigned long long text;
    };
    

    /// \class HubLoadingScene
    /// \brief Hub loading class
    class HubLoadingScene : public AScene {

        public:
            /// \param name : the new name of the current scene
            /// \param ECS : ECS instance to pass to the scene
            /// \brief scene constructor
            HubLoadingScene(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS);
            /// \param name : the new name of the current scene
            /// \param ECS : ECS instance to pass to the scene
            /// \brief scene constructor
            HubLoadingScene(const char *name, std::shared_ptr<Module::EntityComponentSystem> &ECS);
            /// \brief destructor
            ~HubLoadingScene();

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
            /*! state of all player */
            std::vector<HubPlayer> _playerStat;

            /// \brief initilaize all scene's components
            void initComponents();
            /// \param playerNb : number of the player in the hub
            /// \brief modified the player display
            void displayPlayer(unsigned int playerNb);
    };
}