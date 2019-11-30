/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** AScene methods
*/

#include "AScene.hpp"

Scenes::AScene::AScene(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS) : _name(name), _ECS(ECS), _pop(false), _swap(false) {}

Scenes::AScene::AScene(const char *name, std::shared_ptr<Module::EntityComponentSystem> &ECS) : _name(name), _ECS(ECS), _pop(false), _swap(false) {}

Scenes::AScene::AScene(const std::string &name) : _name(name), _pop(false), _swap(false) {}

Scenes::AScene::AScene(const char *name) : _name(name), _pop(false), _swap(false) {}

std::string Scenes::AScene::name() const
{
    return _name;
}

void Scenes::AScene::setName(const std::string &name)
{
    _name = name;
}

bool Scenes::AScene::isToPop() const
{
    return _pop;
}

bool Scenes::AScene::isToSwap() const
{
    return _swap;
}

void Scenes::AScene::setPop(bool pop)
{
    _pop = pop;
}

void Scenes::AScene::setECSInstance(std::shared_ptr<Module::EntityComponentSystem> &ECS)
{
    _ECS = ECS;
}

std::stack<Network::Entity> &Scenes::AScene::entityStack()
{
    return _stack;
}

void Scenes::AScene::pushEntityStack(std::shared_ptr<ECS::Entity> &entity, std::size_t id)
{
    if (entity->hasComponent(ECS::Component::Flags::animation2D) && entity->hasComponent(ECS::Component::Flags::sprite)) {

        _stack.emplace(Network::Entity());

        // Getting the necessary components 
        auto componentAnimation = static_cast<ECS::Component::Animation2D *>(entity->component(ECS::Component::Flags::animation2D).get());
        auto componentTransform = static_cast<ECS::Component::Transform *>(entity->component(ECS::Component::Flags::transform).get());
        auto componentSprite = static_cast<ECS::Component::Sprite *>(entity->component(ECS::Component::Flags::sprite).get());

        // Compying parameters of the compnent into the network entity
        _stack.top().id = id;
        _stack.top().top = componentAnimation->rect.top;
        _stack.top().left = componentAnimation->rect.left;
        _stack.top().width = componentAnimation->rect.width;
        _stack.top().height = componentAnimation->rect.height;
        std::memcpy(_stack.top().texture, componentSprite->texture.c_str(), componentSprite->texture.length());
        _stack.top().x = componentTransform->x;
        _stack.top().y = componentTransform->y;
        _stack.top().z = componentTransform->z;
    } else if (entity->hasComponent(ECS::Component::Flags::sprite)) {

        _stack.emplace(Network::Entity());

        // Getting the necessary components 
        auto componentTransform = static_cast<ECS::Component::Transform *>(entity->component(ECS::Component::Flags::transform).get());
        auto componentSprite = static_cast<ECS::Component::Sprite *>(entity->component(ECS::Component::Flags::sprite).get());

        // Compying parameters of the compnent into the network entity
        _stack.top().id = id;
        _stack.top().top = componentSprite->rect.top;
        _stack.top().left = componentSprite->rect.left;
        _stack.top().width = componentSprite->rect.width;
        _stack.top().height = componentSprite->rect.height;
        std::memcpy(_stack.top().texture, componentSprite->texture.c_str(), componentSprite->texture.length());
        _stack.top().x = componentTransform->x;
        _stack.top().y = componentTransform->y;
        _stack.top().z = componentTransform->z;
    }
}