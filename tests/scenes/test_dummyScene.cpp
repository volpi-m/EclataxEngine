//
// Created by tabis on 10/10/2019.
//

#include "SceneMachine.hpp"
#include "GameEngine.hpp"
#include "DumyScene.hpp"

#include <gtest/gtest.h>

TEST(DummySceneTest, instanciation)
{
    Game::GameEngine engine;
    auto scene = std::shared_ptr<Scenes::IScene>(new Scenes::DumyScene("Dummy scene", engine.ECS()));
    auto scene2 = std::shared_ptr<Scenes::IScene>(new Scenes::DumyScene(std::string("Dummy scene 2"), engine.ECS()));
    auto scene3 = std::shared_ptr<Scenes::IScene>(new Scenes::DumyScene("Dummy scene 3"));
    auto scene4 = std::shared_ptr<Scenes::IScene>(new Scenes::DumyScene(std::string("Dummy scene 4")));

    ASSERT_NE(scene.get(), nullptr);
    ASSERT_NE(scene2.get(), nullptr);
    ASSERT_NE(scene3.get(), nullptr);
    ASSERT_NE(scene4.get(), nullptr);
}

TEST(DummySceneTest, name)
{
    Game::GameEngine engine;
    auto scene = std::shared_ptr<Scenes::IScene>(new Scenes::DumyScene("Dummy scene", engine.ECS()));

    ASSERT_STREQ("Dummy scene", scene->name().c_str());
    scene->setName("New name!");
    ASSERT_STREQ("New name!", scene->name().c_str());
}

TEST(DummySceneTest, run)
{
    Game::GameEngine engine;
    auto scene = std::shared_ptr<Scenes::IScene>(new Scenes::DumyScene("Dummy scene", engine.ECS()));

    ASSERT_EQ(scene->run(), nullptr);
    ASSERT_EQ(scene->run(), nullptr);
}

TEST(DummySceneTest, hideEntities)
{
    Game::GameEngine engine;
    auto scene = std::shared_ptr<Scenes::IScene>(new Scenes::DumyScene("Dummy scene", engine.ECS()));

    ASSERT_EQ(scene->run(), nullptr);
    scene->setVisible(false);
    scene->remove();
    ASSERT_EQ(scene->run(), nullptr);
}

TEST(DummySceneTest, ECSInstance)
{
    Game::GameEngine engine;
    auto scene = std::shared_ptr<Scenes::IScene>(new Scenes::DumyScene("Dummy scene"));

    engine.ECS()->createEntity("test");
    scene->setECSInstance(engine.ECS());
    ASSERT_EQ(scene->run(), nullptr);
}

TEST(DummySceneTest, pop)
{
    Game::GameEngine engine;
    auto scene = std::shared_ptr<Scenes::IScene>(new Scenes::DumyScene("Dummy scene"));

    ASSERT_EQ(scene->isToPop(), false);
    scene->setPop(true);
    ASSERT_EQ(scene->isToPop(), true);
}