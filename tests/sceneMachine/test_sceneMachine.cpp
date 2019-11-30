//
// Created by tabis on 10/10/2019.
//

#include "SceneMachine.hpp"
#include "GameEngine.hpp"
#include "DumyScene.hpp"

#include <gtest/gtest.h>

// TEST(SceneMachineTests, pushScenes)
// {
//     Game::GameEngine engine;
//     Module::SceneMachine machine;
//     auto scene = std::shared_ptr<Scenes::IScene>(new Scenes::DumyScene("Dummy scene", engine.ECS()));

//     ASSERT_EQ(machine.size(), 0);
//     machine.push(scene);
//     ASSERT_EQ(machine.size(), 1);
//     machine.push(scene);
//     ASSERT_EQ(machine.size(), 2);
// }

// TEST(SceneMachineTests, popScenes)
// {
//     Game::GameEngine engine;
//     Module::SceneMachine machine;
//     auto scene = std::shared_ptr<Scenes::IScene>(new Scenes::DumyScene("Dummy scene", engine.ECS()));
//     auto scene2 = std::shared_ptr<Scenes::IScene>(new Scenes::DumyScene("Dummy scene 2", engine.ECS()));
//     auto scene3 = std::shared_ptr<Scenes::IScene>(new Scenes::DumyScene("Dummy scene 3", engine.ECS()));

//     ASSERT_EQ(machine.size(), 0);
//     machine.push(scene);
//     ASSERT_EQ(machine.size(), 1);
//     machine.pop();
//     ASSERT_EQ(machine.size(), 0);
//     machine.push(scene);
//     machine.push(scene2);
//     machine.push(scene3);
//     ASSERT_EQ(machine.size(), 3);
//     machine.pop("Dummy scene");
//     ASSERT_EQ(machine.size(), 1);
//     machine.push(scene2);
//     machine.push(scene3);
//     ASSERT_EQ(machine.size(), 3);
//     machine.pop(std::string("Dummy scene"));
//     ASSERT_EQ(machine.size(), 1);
// }

// TEST(SceneMachineTests, swapScenes)
// {
//     Game::GameEngine engine;
//     Module::SceneMachine machine;
//     auto scene = std::shared_ptr<Scenes::IScene>(new Scenes::DumyScene("Dummy scene", engine.ECS()));
//     auto scene2 = std::shared_ptr<Scenes::IScene>(new Scenes::DumyScene("Swapped scene", engine.ECS()));

//     ASSERT_EQ(machine.size(), 0);
//     machine.push(scene);
//     ASSERT_EQ(machine.size(), 1);
//     ASSERT_STREQ("Dummy scene", machine.name().c_str());
//     machine.swap(scene2);
//     ASSERT_EQ(machine.size(), 1);
//     ASSERT_STREQ("Swapped scene", machine.name().c_str());
// }

// TEST(SceneMachineTests, isToPopAndSwapScene)
// {
//     Game::GameEngine engine;
//     Module::SceneMachine machine;
//     auto scene = std::shared_ptr<Scenes::IScene>(new Scenes::DumyScene("Dummy scene", engine.ECS()));

//     scene->setPop(true);
//     ASSERT_EQ(machine.isToPop(), false);
//     ASSERT_EQ(machine.isToSwap(), false);
//     machine.push(scene);
//     ASSERT_EQ(machine.isToPop(), true);
//     ASSERT_EQ(machine.isToSwap(), false);
// }

// TEST(SceneMachineTests, runScene)
// {
//     Game::GameEngine engine;
//     Module::SceneMachine machine;
//     auto scene = std::shared_ptr<Scenes::IScene>(new Scenes::DumyScene("Dummy scene", engine.ECS()));

//     machine.push(scene);
//     ASSERT_EQ(machine.run(), true);
//     ASSERT_EQ(machine.run(), false);
// }