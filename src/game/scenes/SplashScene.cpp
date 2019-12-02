/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** splash screen
*/

#include "SplashScene.hpp"

Scenes::SplashScene::SplashScene(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS, int players) : AScene(name, ECS, players) { }

Scenes::SplashScene::SplashScene(const char *name, std::shared_ptr<Module::EntityComponentSystem> &ECS, int players) : AScene(name, ECS, players)
{
    Debug::Logger *l = Debug::Logger::getInstance();
    l->generateDebugMessage(Debug::type::INFO , "Let's build a wall !", "SplashScene::constructor()");
    initComponents();
}

Scenes::SplashScene::SplashScene(int players, const std::string &name) : AScene(players, name) {}

Scenes::SplashScene::SplashScene(int players, const char *name) : AScene(players, name) {}

Scenes::IScene *Scenes::SplashScene::run()
{
    auto sps = _ECS->entity(_ids.front());
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

void Scenes::SplashScene::setVisible(bool state)
{
    state = state;
}

void Scenes::SplashScene::remove()
{
    
}

void Scenes::SplashScene::initComponents()
{
    std::shared_ptr<ECS::ISystem> systemIA(new ECS::System::IASystem);
    std::shared_ptr<ECS::ISystem> systemAnimation(new ECS::System::AnimationSystem);
    std::shared_ptr<ECS::ISystem> systemMovement(new ECS::System::MovementSystem);
    std::shared_ptr<ECS::ISystem> systemSpawn(new ECS::System::SpawnerSystem);
    std::shared_ptr<ECS::ISystem> systemLifeSpan(new ECS::System::LifeSpanSystem);

    _ids.push_back(_ECS->createEntityFromLibrary("lib/libship.so"));
    _ids.push_back(_ECS->createEntity("Background"));

    _ECS->addSystem(ECS::System::Flags::IA, systemIA);
    _ECS->addSystem(ECS::System::Flags::Animation, systemAnimation);
    _ECS->addSystem(ECS::System::Flags::Movement, systemMovement);
    _ECS->addSystem(ECS::System::Flags::Spawner, systemSpawn);
    _ECS->addSystem(ECS::System::Flags::LifeSpan, systemLifeSpan);
}

void Scenes::SplashScene::handleEvent(std::queue<std::pair<int, size_t>> events)
{
    auto sps = _ECS->entity(_ids.front());
    auto movementSystem = static_cast<ECS::System::MovementSystem *>(_ECS->system(ECS::System::Flags::Movement).get());

    while(!events.empty()) {
        if ((events.front().second & Scenes::Event::UP) == Scenes::Event::UP) {
            std::cout << "Player press Z" << std::endl;
            movementSystem->move(sps, 2, 0, 0);
        }
        if ((events.front().second & Scenes::Event::DOWN) == Scenes::Event::DOWN) {
            std::cout << "Player press S" << std::endl;
            movementSystem->move(sps, 2, 0, 0);
        }
        events.pop();
    }
}
