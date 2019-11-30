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
        std::unique_ptr<ECS::ISystem> movement(new ECS::System::MovementSystem);
        std::unique_ptr<ECS::ISystem> iA(new ECS::System::IASystem);
        std::unique_ptr<ECS::ISystem> spawner(new ECS::System::SpawnerSystem);

        // Creating the entity, adding the component, saving the system
        _ids.push_back(_ECS->createEntity("John Cena"));

        // Creating an asteriod from a dynamic librart
        auto id = _ECS->createEntityFromLibrary("lib/libship.so");
        if (id)
            _ids.push_back(id);
        _ECS->addComponentToEntity(_ids.front(), ECS::Component::Flags::transform, transform);
        _ECS->addSystem(ECS::System::Flags::Movement, movement);
        _ECS->addSystem(ECS::System::Flags::IA, iA);
        _ECS->addSystem(ECS::System::Flags::Spawner, spawner);
    } else if (_ECS->hasEntity(_ids.front())) {
        std::cout << std::endl << "The Dumy scene posseses " << _ids.size() << " entitie(s)" << std::endl;
        for (auto &it : _ids)
            std::cout << "- " << _ECS->tag(it) << std::endl;
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
        if (_ids.size() == 1)
            _pop = true;
        else {
            // Getting the position of an entity via the system
            auto positionShip = movementSystem->transform(_ECS->entity(_ids.back()));

            if (std::get<0>(positionShip) < -960) {

                std::cout << "ship out of range !" << std::endl;
                _ECS->deleteEntity(_ids.back());
                _ids.erase(_ids.end() - 1);
            }
        }
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

std::stack<Network::Entity> &Scenes::DumyScene::entityStack()
{
    return _stack;
}

void Scenes::DumyScene::pushEntityStack(std::shared_ptr<ECS::Entity> &entity, std::size_t id)
{
    if (entity->hasComponent(ECS::Component::Flags::animation2D) && entity->hasComponent(ECS::Component::Flags::sprite)) {

        _stack.emplace(Network::Entity());

        // Getting the animation component 
        auto componentAnimation = static_cast<ECS::Component::Animation2D *>(entity->component(ECS::Component::Flags::animation2D).get());
        auto componentSprite = static_cast<ECS::Component::Sprite *>(entity->component(ECS::Component::Flags::sprite).get());
        auto componentTransform = static_cast<ECS::Component::Transform *>(entity->component(ECS::Component::Flags::transform).get());

        // Compying parameters of the compnent into the network entity
        _stack.top().id = id;
        _stack.top().top = componentAnimation->rect.top;
        _stack.top().left = componentAnimation->rect.left;
        _stack.top().width = componentAnimation->rect.width;
        _stack.top().height = componentAnimation->rect.height;
        std::memcpy(_stack.top().texture, "ressources/r-typesheet1.gif", 27);
        _stack.top().x = componentTransform->x;
        _stack.top().y = componentTransform->y;
        _stack.top().z = componentTransform->z;
    }
}

void Scenes::DumyScene::handleEvent([[maybe_unused]]std::queue<std::pair<int, size_t>> &events)
{
    std::cout << "I'm handling event (lol it's not true)" << std::endl;
}