/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** text class methods
*/

#include "TextSystem.hpp"

void ECS::System::TextSystem::update([[maybe_unused]]std::unordered_map<unsigned long long, std::shared_ptr<Entity>> &entities)
{
}

const std::string& ECS::System::TextSystem::text(std::shared_ptr<Entity> &entity) const
{
    auto component = static_cast<ECS::Component::Text *>(entity->component(Component::Flags::text).get());

    return component->text;
}

const std::string& ECS::System::TextSystem::font(std::shared_ptr<Entity> &entity) const
{
    auto component = static_cast<ECS::Component::Text *>(entity->component(Component::Flags::text).get());

    return component->font;
}

void ECS::System::TextSystem::setText(std::shared_ptr<Entity> &entity, const std::string &newText)
{
    auto component = static_cast<ECS::Component::Text *>(entity->component(Component::Flags::text).get());
    component->text = newText;
}

void ECS::System::TextSystem::setFont(std::shared_ptr<Entity> &entity, const std::string &newFont)
{
    auto component = static_cast<ECS::Component::Text *>(entity->component(Component::Flags::text).get());
    component->font = newFont;
}