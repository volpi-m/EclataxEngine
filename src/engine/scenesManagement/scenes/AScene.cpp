
#include "AScene.hpp"

void Scenes::AScene::onInit(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS, Module::IMediator *mediator)
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