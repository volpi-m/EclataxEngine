
#include "AScene.hpp"

Scenes::AScene::AScene(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS, std::shared_ptr<Module::IMediator> &mediator) : _name(name), _mediator(mediator), _ECS(ECS) {}

void Scenes::AScene::onInit(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS, std::shared_ptr<Module::IMediator> &mediator)
{
    _name = name;
    _ECS = ECS;
    _mediator = mediator;
}

void Scenes::AScene::setName(const std::string &name)
{
    _name = name;
}

std::string Scenes::AScene::name() const
{
    return _name;
}