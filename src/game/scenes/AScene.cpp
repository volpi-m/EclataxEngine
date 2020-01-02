/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** AScene methods
*/

#include "AScene.hpp"

Scenes::AScene::AScene(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS, int players) : _name(name), _ECS(ECS), _pop(false), _swap(false), _players(players) {}

Scenes::AScene::AScene(const char *name, std::shared_ptr<Module::EntityComponentSystem> &ECS, int players) : _name(name), _ECS(ECS), _pop(false), _swap(false), _players(players) {}

Scenes::AScene::AScene(int players, const std::string &name) : _name(name), _pop(false), _swap(false), _players(players) {}

Scenes::AScene::AScene(int players, const char *name) : _name(name), _pop(false), _swap(false), _players(players) {}

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

void Scenes::AScene::copyAnimation(std::shared_ptr<ECS::Entity> &entity, Network::Entity &top) const
{
    auto componentAnimation = static_cast<ECS::Component::Animation2D *>(entity->component(ECS::Component::Flags::animation2D).get());
    
    // Copying the animation rect.
    top.top = componentAnimation->rect.top;
    top.left = componentAnimation->rect.left;
    top.width = componentAnimation->rect.width;
    top.height = componentAnimation->rect.height;
}

void Scenes::AScene::copySprite(std::shared_ptr<ECS::Entity> &entity, Network::Entity &top) const
{
    auto componentSprite = static_cast<ECS::Component::Sprite *>(entity->component(ECS::Component::Flags::sprite).get());
    
    // Copying the sprite rect.
    top.top = componentSprite->rect.top;
    top.left = componentSprite->rect.left;
    top.width = componentSprite->rect.width;
    top.height = componentSprite->rect.height;
}

void Scenes::AScene::copyTransform(std::shared_ptr<ECS::Entity> &entity, Network::Entity &top) const
{
    auto componentTransform = static_cast<ECS::Component::Transform *>(entity->component(ECS::Component::Flags::transform).get());
    
    // Copying the transform component.
    top.x = componentTransform->x;
    top.y = componentTransform->y;
    top.z = componentTransform->z;
}

void Scenes::AScene::pushEntityStack(std::shared_ptr<ECS::Entity> &entity, std::size_t id)
{
    // If the entity hasn't been updated, we don't need to add it to the stack.
    if (!entity->updated() && !entity->deleted())
        return;

    // If there is at minimum a sprite to render and a transform, update the entity on the client.
    if (entity->hasComponent(ECS::Component::Flags::sprite) && entity->hasComponent(ECS::Component::Flags::transform)) {

        // Creating the entity at the top of the stack
        _stack.emplace(Network::Entity());

        // Getting the necessary components 
        auto componentSprite = static_cast<ECS::Component::Sprite *>(entity->component(ECS::Component::Flags::sprite).get());

        // Copying parameters of the component into the network entity.
        _stack.top().id = id;
        
        // Copying the animation rect component if there is one, sprite rect otherwise. 
        if (entity->hasComponent(ECS::Component::Flags::animation2D))
            copyAnimation(entity, _stack.top());
        else
            copySprite(entity, _stack.top());

        // Copying the transform component.
        copyTransform(entity, _stack.top());
        
        // check updated and deleted fields
        _stack.top().deleted = entity->deleted() || !componentSprite->loaded ? 1 : 0;

        // copy texture
        std::memcpy(_stack.top().texture, componentSprite->texture.c_str(), componentSprite->texture.length());
    }

    // Reset the update field.
    entity->update(false);
}