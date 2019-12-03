/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Parallax
*/

#include "Parallax2.hpp"

extern "C" ECS::Entity *entryPoint()
{
    Game::Parallax2 parallax;

    return parallax.createEntity();
}

ECS::Entity *Game::Parallax2::createEntity()
{
    ECS::Entity *bg = new ECS::Entity("Background");
    Game::Rect rect(0, 0, 1920, 1080);

    std::shared_ptr<ECS::IComponent> sprite(new ECS::Component::Sprite("ressources/level_2.png", rect));
    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform(0, 0, 0));
    std::shared_ptr<ECS::IComponent> animation(new ECS::Component::Animation2D(std::chrono::milliseconds(10), rect, 1920, 2));

    bg->addComponent(ECS::Component::Flags::sprite, sprite);
    bg->addComponent(ECS::Component::Flags::transform, transform);
    bg->addComponent(ECS::Component::Flags::animation2D, animation);

    return bg;
}