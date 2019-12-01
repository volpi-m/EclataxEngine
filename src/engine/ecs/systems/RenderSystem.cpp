/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** MovementSystem class methods
*/

#include "RenderSystem.hpp"

void ECS::System::RenderSystem::update([[maybe_unused]]std::unordered_map<unsigned long long, std::shared_ptr<Entity>> &entities)
{ }

std::string ECS::System::RenderSystem::texture(std::shared_ptr<ECS::Entity> &entity) const
{
    // Casting the correct component
    auto component = static_cast<ECS::Component::Sprite *>(entity->component(Component::Flags::sprite).get());

    // returning the texture attribute
    return component->texture;
}

void ECS::System::RenderSystem::setTexture(std::shared_ptr<ECS::Entity> &entity, const std::string &texture)
{
    // Casting the correct component
    auto component = static_cast<ECS::Component::Sprite *>(entity->component(Component::Flags::sprite).get());

    // Setting the new texture file
    component->texture = texture;
}

void ECS::System::RenderSystem::setLoaded(std::shared_ptr<ECS::Entity> &entity)
{
    // Casting the correct component
    auto component = static_cast<ECS::Component::Sprite *>(entity->component(Component::Flags::sprite).get());

    // the sprite as been loaded
    component->loaded = true;
}

bool ECS::System::RenderSystem::loaded(const std::shared_ptr<ECS::Entity> &entity) const
{
    auto component = static_cast<ECS::Component::Sprite *>(entity->component(Component::Flags::sprite).get());

    // getting the current value of the loaded attribute
    return component->loaded;
}