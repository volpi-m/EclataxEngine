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

bool Scenes::SplashScene::run()
{
    Debug::Logger *l = Debug::Logger::getInstance();
    l->generateDebugMessage(Debug::type::INFO , "Why are you running ?", "SplashScene::run()");
    return false;
}

void Scenes::SplashScene::setVisible(bool state)
{

}

void Scenes::SplashScene::remove()
{

}

void Scenes::SplashScene::initComponents()
{
    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform());
    std::unique_ptr<ECS::ISystem> system(new ECS::System::MovementSystem);
    _ids.push_back(_ECS->createEntity("Spaceship"));
    _ECS->addComponentToEntity(_ids.front(), ECS::Component::Flags::transform, transform);
    _ECS->addSystem(ECS::System::Flags::Movement, system);
}