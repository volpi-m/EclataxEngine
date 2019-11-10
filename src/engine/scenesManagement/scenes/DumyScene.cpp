//
// EPITECH PROJECT, 2019
// DumyScene.cpp
// File description:
// dumy scene
//

/// \file DumyScene.cpp
/// \author Lucas T.
/// \brief DumyScene class methods

#include "DumyScene.hpp"

Scenes::DumyScene::DumyScene(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS) : _name(name), _ECS(ECS), _pop(true), _swap(false) {}
Scenes::DumyScene::DumyScene(const char *name, std::shared_ptr<Module::EntityComponentSystem> &ECS) : _name(name), _ECS(ECS), _pop(true), _swap(false) {}
Scenes::DumyScene::DumyScene(const std::string &name) : _name(name), _pop(true), _swap(false) {}
Scenes::DumyScene::DumyScene(const char *name) : _name(name), _pop(true), _swap(false) {}

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
    if (_ids.empty())
        _ids.push_back(_ECS->createEntity("John Cena"));
    else
        std::cout << "The Dumy scene posseses " << _ids.size() << " entitie(s), it's name is " << _ECS->tag(_ids.front()) << std::endl;
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
    for (auto &it : _ids)
        _ECS->setEntityVisibleState(it, state);
}

void Scenes::DumyScene::remove()
{

}

void Scenes::DumyScene::setECSInstance(std::shared_ptr<Module::EntityComponentSystem> &ECS)
{
    _ECS = ECS;
}