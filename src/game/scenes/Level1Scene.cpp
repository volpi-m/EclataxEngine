/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** splash screen
*/

#include "Level1Scene.hpp"

Scenes::Level1Scene::Level1Scene(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS) : AScene(name, ECS) { }

Scenes::Level1Scene::Level1Scene(const char *name, std::shared_ptr<Module::EntityComponentSystem> &ECS) : AScene(name, ECS)
{
    Debug::Logger *l = Debug::Logger::getInstance();
    l->generateDebugMessage(Debug::type::INFO , "Let's build a wall !", "Level1Scene::constructor()");
    initComponents();
}

Scenes::Level1Scene::Level1Scene(const std::string &name) : AScene(name) {}

Scenes::Level1Scene::Level1Scene(const char *name) : AScene(name) {}

Scenes::IScene *Scenes::Level1Scene::run()
{
    auto sps = _ECS->entity(_ids.at(1));
    auto movementSystem = static_cast<ECS::System::MovementSystem *>(_ECS->system(ECS::System::Flags::Movement).get());

    _ids = _ECS->ids();
    if (std::get<0>(movementSystem->transform(sps)) > 0) {
        _ECS->update();
        for (unsigned long long id = 0; id < _ids.size() && _ECS->hasEntity(_ids[id]); ++id)
            pushEntityStack(_ECS->entity(_ids[id]), _ids[id]);
        _ECS->clearEntities();
        return nullptr;
    } else {
        movementSystem->setTransform(sps, 1920, std::get<1>(movementSystem->transform(sps)), 0);
        return nullptr;
    }
}

void Scenes::Level1Scene::setVisible(bool state)
{
    state = state;
}

void Scenes::Level1Scene::remove()
{
    
}

void Scenes::Level1Scene::initComponents()
{
    std::unique_ptr<ECS::ISystem> systemIA(new ECS::System::IASystem);
    std::unique_ptr<ECS::ISystem> systemAnimation(new ECS::System::AnimationSystem);
    std::unique_ptr<ECS::ISystem> systemMovement(new ECS::System::MovementSystem);
    std::unique_ptr<ECS::ISystem> systemSpawn(new ECS::System::SpawnerSystem);
    std::unique_ptr<ECS::ISystem> systemLifeSpan(new ECS::System::LifeSpanSystem);

    std::shared_ptr<ECS::IComponent> sprite(new ECS::Component::Sprite("ressources/level_1.jpg", Game::Rect(0, 0, 1920, 1080)));
    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform);

    _ids.push_back(_ECS->createEntity("Background"));
    _ids.push_back(_ECS->createEntityFromLibrary("lib/libship.so"));

    _ECS->addComponentToEntity(_ids.front(), ECS::Component::Flags::sprite, sprite);
    _ECS->addComponentToEntity(_ids.front(), ECS::Component::Flags::transform, transform);

    _ECS->addSystem(ECS::System::Flags::IA, systemIA);
    _ECS->addSystem(ECS::System::Flags::Animation, systemAnimation);
    _ECS->addSystem(ECS::System::Flags::Movement, systemMovement);
    _ECS->addSystem(ECS::System::Flags::Spawner, systemSpawn);
    _ECS->addSystem(ECS::System::Flags::LifeSpan, systemLifeSpan);
}

void Scenes::Level1Scene::handleEvent(std::queue<std::pair<int, size_t>> &events)
{
    auto sps = _ECS->entity(_ids.front());
    auto movementSystem = static_cast<ECS::System::MovementSystem *>(_ECS->system(ECS::System::Flags::Movement).get());

    while(!events.empty()) {
        if ((events.front().second & 1) == 1) {
            movementSystem->move(sps, 2, 0, 0);
        }
        if ((events.front().second & 2) == 2) {
            movementSystem->move(sps, 2, 0, 0);
        }
        events.pop();
    }
}
