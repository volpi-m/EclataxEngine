/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** AScene methods
*/

#include "AScene.hpp"

Scenes::AScene::AScene(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS) : _name(name), _ECS(ECS), _pop(true), _swap(false) {}

Scenes::AScene::AScene(const char *name, std::shared_ptr<Module::EntityComponentSystem> &ECS) : _name(name), _ECS(ECS), _pop(true), _swap(false) {}

Scenes::AScene::AScene(const std::string &name) : _name(name), _pop(true), _swap(false) {}

Scenes::AScene::AScene(const char *name) : _name(name), _pop(true), _swap(false) {}

std::string Scenes::AScene::name() const
{
    return _name;
}

void Scenes::AScene::setName(const std::string &name)
{
    _name = name;
}

bool Scenes::AScene::isToPop() const
{
    return _pop;
}

bool Scenes::AScene::isToSwap() const
{
    return _swap;
}

void Scenes::AScene::setPop(bool pop)
{
    _pop = pop;
}

void Scenes::AScene::setECSInstance(std::shared_ptr<Module::EntityComponentSystem> &ECS)
{
    _ECS = ECS;
}
