/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** splash screen
*/

#include "SplashScene.hpp"

Scenes::SplashScene::SplashScene(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS) : AScene(name, ECS) { }

Scenes::SplashScene::SplashScene(const char *name, std::shared_ptr<Module::EntityComponentSystem> &ECS) : AScene(name, ECS)
{
    Debug::Logger *l = Debug::Logger::getInstance();
    l->generateDebugMessage(Debug::type::INFO , "Let's build a wall !", "SplashScene::constructor()");
    initComponents();
}

Scenes::SplashScene::SplashScene(const std::string &name) : AScene(name) {}

Scenes::SplashScene::SplashScene(const char *name) : AScene(name) {}

Scenes::IScene *Scenes::SplashScene::run()
{
    auto sps = _ECS->entity(_ids.front());
    auto movementSystem = static_cast<ECS::System::MovementSystem *>(_ECS->system(ECS::System::Flags::Movement).get());

    std::cout << std::get<0>(movementSystem->transform(sps)) << std::endl;
    if (std::get<0>(movementSystem->transform(sps)) < 1920) {
        movementSystem->move(sps, 10, 0, 0);
        pushEntityStack(sps);
        return nullptr;
    } else {
        movementSystem->setTransform(sps, 0, 0, 0);
        return nullptr;
    }
}

void Scenes::SplashScene::setVisible(bool state)
{
    state = state;
}

void Scenes::SplashScene::remove()
{
    
}

void Scenes::SplashScene::initComponents()
{
    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform());
    std::shared_ptr<ECS::IComponent> sprite(new ECS::Component::Sprite("ressources/r-typesheet1.gif", Game::Rect(0, 32, 32, 32)));
    std::unique_ptr<ECS::ISystem> system(new ECS::System::MovementSystem);

    _ids.push_back(_ECS->createEntity("Spaceship"));
    _ids.push_back(_ECS->createEntity("Background"));

    _ECS->addComponentToEntity(_ids.front(), ECS::Component::Flags::transform, transform);
    _ECS->addComponentToEntity(_ids.front(), ECS::Component::Flags::sprite, sprite);
    _ECS->addSystem(ECS::System::Flags::Movement, system);
}

void Scenes::SplashScene::handleEvent(std::queue<std::pair<int, size_t>> &events)
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