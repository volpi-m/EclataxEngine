/*
** EPITECH PROJECT, 2019
** IScene.hpp
** File description:
** IScene class
*/

#pragma once

namespace indie {
    class IScene {
        public:
            virtual ~IScene() = default;
            virtual void setName(const std::string &name) = 0;
            virtual std::string getName() const = 0;
            virtual indie::IScene *computeEvents() = 0;
            virtual bool isToPop() const = 0;
            virtual bool isToSwap() const = 0;
            virtual void setPop(bool b) = 0;
            virtual void setVisible(bool b) = 0;
            virtual void remove() = 0;
    };
}