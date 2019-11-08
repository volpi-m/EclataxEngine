//
// EPITECH PROJECT, 2019
// DumyScene.hpp
// File description:
// DumyScene class declaration
//

#pragma once

#include <string>
#include <memory>

#include "IScene.hpp"
#include "Logger.hpp"

namespace Scenes {

    class DumyScene : public IScene {
        public:
            DumyScene() = default;
            ~DumyScene() override = default;

            /// \param name : the new name of the current scene
            /// \brief change the name of the scene
            void setName(const std::string &name) override;

            /// \return the name of the current scene
            /// \brief get the name of the current scene
            std::string name() const override;

            /// \return a bool representing the state of the scene
            /// \brief run the scenes logic
            bool run() override;
            
            /// \return a bool if the scene needs to be poped when destroyed
            /// \brief scene deletion characteristic
            bool isToPop() const override;

            /// \return a bool if the scene needs to be swaped when destroyed
            /// \brief scene deletion characteristic
            bool isToSwap() const override;

            /// \param bool : the visible state of the scene
            /// \brief set visible state of the scene
            void setVisible(bool state) override;

            /// \brief remove all the entities of the scene
            void remove() override;

        private:
            std::string _name;
            bool _pop;
            bool _swap;
    };
}