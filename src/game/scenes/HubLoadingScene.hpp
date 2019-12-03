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
#include "RenderSystem.hpp"
#include "MovementSystem.hpp"

/// \namespace Scenes
/// \brief Used for all scenes
namespace Scenes {

    /// \def PLAYER_SHIP_PATH
    /// \brief path to player library
    constexpr const auto PLAYER_SHIP_PATH = "lib/libplayer.so";

    /// \def CHECK_PATH
    /// \brief path to check image to check ready in hub
    constexpr const auto CHECK_PATH = "ressources/check.png";

    /// \def CROSS_PATH
    /// \brief path to cross image to select no ready in hub
    constexpr const auto CROSS_PATH = "ressources/cross.png";

    /// \struct HubPlayer
    /// \brief Represent info to know if a specific player is ready or not
    struct HubPlayer
    {
        HubPlayer(bool state, unsigned long long ico) : state(state), ico(ico) {};
        /*! state of player */
        bool state;
        /*! id of player icon */
        unsigned long long ico;
    };
    

    /// \class HubLoadingScene
    /// \brief Hub loading class
    class HubLoadingScene : public AScene {

        public:
            /// \param name : the new name of the current scene
            /// \param ECS : ECS instance to pass to the scene
            /// \brief scene constructor
            HubLoadingScene(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS, int player);
            /// \param name : the new name of the current scene
            /// \param ECS : ECS instance to pass to the scene
            /// \brief scene constructor
            HubLoadingScene(const char *name, std::shared_ptr<Module::EntityComponentSystem> &ECS, int player);
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
            void handleEvent(std::queue<std::pair<int, size_t>> events);

            /// \param playerNb : numbre of player
            /// \param state : state of the player
            /// \brief modified the player display
            void setPlayerReady(int playerNb, bool state);

        private:
            /*! state of all player */
            std::vector<HubPlayer> _playerStat;

            /// \brief initilaize all scene's components
            void initComponents();
            /// \param playerNb : number of the player in the hub
            /// \brief modified the player display
            void displayPlayer(int playerNb);
            /// \param nb : number of the concerned player
            /// \brief create info category for one player
            void createCategory(int nb);
    };
}