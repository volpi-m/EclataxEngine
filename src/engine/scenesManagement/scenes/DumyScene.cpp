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

Scenes::DumyScene::DumyScene(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS) : _name(name), _ECS(ECS), _pop(false), _swap(false) {}
Scenes::DumyScene::DumyScene(const char *name, std::shared_ptr<Module::EntityComponentSystem> &ECS) : _name(name), _ECS(ECS), _pop(false), _swap(false) {}
Scenes::DumyScene::DumyScene(const std::string &name) : _name(name), _pop(false), _swap(false) {}
Scenes::DumyScene::DumyScene(const char *name) : _name(name), _pop(false), _swap(false) {}

void Scenes::DumyScene::setName(const std::string &name)
{
    _name = name;
}

std::string Scenes::DumyScene::name() const
{
    return _name;
}

Scenes::IScene *Scenes::DumyScene::run()
{
    if (_ids.empty()) {
        // Creating a basic component to add to an entity, and a system that wil access it.
        std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform(0, 1, 2));
        std::unique_ptr<ECS::ISystem> system(new ECS::System::MovementSystem);

        // Creating the entity, adding the component, saving the system
        _ids.push_back(_ECS->createEntity("John Cena"));
        _ECS->addComponentToEntity(_ids.front(), ECS::Component::Flags::transform, transform);
        _ECS->addSystem(ECS::System::Flags::Movement, system);
    } else if (_ECS->hasEntity(_ids.front())) {
        std::cout << "The Dumy scene posseses " << _ids.size() << " entitie(s), it's name is " << _ECS->tag(_ids.front()) << std::endl;
        std::cout << "Launching systems ..." << std::endl;

        // Getting the system that we want to use
        auto movementSystem = static_cast<ECS::System::MovementSystem *>(_ECS->system(ECS::System::Flags::Movement).get());

        // Getting the position of an entity via the system
        auto position = movementSystem->transform(_ECS->entity(_ids.front()));

        // Setting new coordinates
        movementSystem->setTransform(_ECS->entity(_ids.front()),
                        std::get<0>(position) + 50,
                        std::get<1>(position) + 50,
                        std::get<2>(position) + 50);

        // Moving the entity
        movementSystem->move(_ECS->entity(_ids.front()), 10, 10, 10);

        // Updating systems
        _ECS->update();
        _ECS->update();
        _pop = true;
        return nullptr;
    }
    return nullptr;
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

void Scenes::DumyScene::setPop(bool pop)
{
    _pop = pop;
}

void Scenes::DumyScene::remove()
{

}

void Scenes::DumyScene::setECSInstance(std::shared_ptr<Module::EntityComponentSystem> &ECS)
{
    _ECS = ECS;
}