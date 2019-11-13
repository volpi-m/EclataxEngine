//
// Created by tabis on 10/10/2019.
//

#include "GameEngine.hpp"
#include <gtest/gtest.h>

TEST(GameEngineTests, ECSInstance)
{
    Game::GameEngine engine;

    ASSERT_NE(engine.ECS(), nullptr);
}

// TEST(GameEngineTests, LibLoaderInstance)
// {
//     Game::GameEngine engine;

//     ASSERT_NE(engine.ECS(), nullptr);
// }

TEST(GameEngineTests, SceneMachineInstance)
{
    Game::GameEngine engine;

    ASSERT_NE(engine.SceneMachine(), nullptr);
}

TEST(GameEngineTests, InitialisedMethod)
{
    Game::GameEngine engine;

    ASSERT_EQ(engine.isInitialised(), true);
}