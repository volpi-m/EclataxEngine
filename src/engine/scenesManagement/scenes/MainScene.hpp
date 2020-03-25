//
// EPITECH PROJECT, 2019
// MainScene.hpp
// File description:
// MainScene class declaration
//

/// \file MainScene.hpp
/// \author Lucas T.
/// \brief MainScene class declaration

#pragma once

#include "AScene.hpp"
#include "Logger.hpp"

#include "SceneStateMachine.hpp"

namespace Scenes
{

    class MainScene : public AScene
    {
    public:

        MainScene() = default;

    	void onUpdate(float deltaTime) override;

        void onCreate() override;

    	void onDestroy() override;

    	void onActivate() override;

    	void onDeactivate() override;
    };
}