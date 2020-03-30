/*
** EPITECH PROJECT, 2019
** IScene.hpp
** File description:
** IScene class interface
*/

#pragma once

#include "ECS.hpp"

// Forward declaration of the mediator interface.
namespace Module
{
    class IMediator;
}

/// \namespace Scene
/// \brief Used for all scenes components
namespace Scenes
{
    /// \class IScene
    /// \brief Scene interface
    class IScene
    {
        public:

            virtual ~IScene() = default;

            virtual void onInit(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS, Module::IMediator *mediator) = 0;

            virtual void onCreate() = 0;

            virtual void onDestroy() = 0;

            virtual void onActivate() = 0;

            virtual void onDeactivate() = 0;

            virtual void onUpdate(float deltaTime) = 0;

            virtual void setName(const std::string &name) = 0;

            virtual std::string name() const = 0;
    };
}