//
// EPITECH PROJECT, 2019
// DumyScene.cpp
// File description:
// dumy scene
//

#include "DumyScene.hpp"

void Scenes::DumyScene::setName(const std::string &name)
{
    _name = name;
}

std::string Scenes::DumyScene::name() const
{
    return _name;
}

bool Scenes::DumyScene::run()
{
    Debug::Logger *log = Debug::Logger::getInstance();

    log->generateDebugMessage(Debug::INFO, "The dummy scene is running", "Scenes::GameScene::run()");
    return true;
}

bool Scenes::DumyScene::isToPop() const
{
    return _pop;
}

bool Scenes::DumyScene::isToSwap() const
{
    return _swap;
}

void Scenes::DumyScene::setVisible(bool state)
{
    (void)state;
}

void Scenes::DumyScene::remove()
{

}