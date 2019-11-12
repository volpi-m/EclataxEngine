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
    if (_ids.empty()) {
        // Creating a basic component to add to an entity, and a system that wil access it.
        std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform(0, 1, 2));
        std::unique_ptr<ECS::ISystem> system(new ECS::System::MovementSystem);

        // Creating the entity, adding the component, saving the system
        _ids.push_back(_ECS->createEntity("John Cena"));
        _ECS->addComponentToEntity(_ids.front(), ECS::Flags::transform, transform);
        _ECS->addSystem(system);
    } else {
        std::cout << "The Dumy scene posseses " << _ids.size() << " entitie(s), it's name is " << _ECS->tag(_ids.front()) << std::endl;
        std::cout << "Launching systems ..." << std::endl;
        _ECS->update();
        return false;
    }
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