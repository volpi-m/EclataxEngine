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

    if (std::get<0>(movementSystem->transform(sps)) > 0) {
        _ECS->update();
        for (unsigned long long id = 0; _ECS->hasEntity(id); ++id)
            pushEntityStack(_ECS->entity(id), id);
        return nullptr;
    } else {
        movementSystem->setTransform(sps, 1920, std::get<1>(movementSystem->transform(sps)), 0);
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
    std::unique_ptr<ECS::ISystem> systemIA(new ECS::System::IASystem);
    std::unique_ptr<ECS::ISystem> systemAnimation(new ECS::System::AnimationSystem);
    std::unique_ptr<ECS::ISystem> systemMovement(new ECS::System::MovementSystem);
    std::unique_ptr<ECS::ISystem> systemSpawn(new ECS::System::SpawnerSystem);

    _ids.push_back(_ECS->createEntityFromLibrary("lib/libship.so"));
    _ids.push_back(_ECS->createEntity("Background"));

    _ECS->addSystem(ECS::System::Flags::IA, systemIA);
    _ECS->addSystem(ECS::System::Flags::Animation, systemAnimation);
    _ECS->addSystem(ECS::System::Flags::Movement, systemMovement);
    _ECS->addSystem(ECS::System::Flags::Spawner, systemSpawn);
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
