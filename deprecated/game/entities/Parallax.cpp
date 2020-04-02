/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Parallax
*/

#include "Parallax.hpp"

extern "C" ECS::Entity *entryPoint()
{
    Game::Parallax parallax;

    return parallax.createEntity();
}

ECS::Entity *Game::Parallax::createEntity()
{
    ECS::Entity *bg = new ECS::Entity("Background");
    Game::Rect rect(0, 0, 1920, 1080);

    std::shared_ptr<ECS::IComponent> sprite(new ECS::Component::Sprite("ressources/level_1.jpg", rect));
    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform(0, 0, 0));
    std::shared_ptr<ECS::IComponent> animation(new ECS::Component::Animation2D(std::chrono::milliseconds(10), rect, 1920, 2));

    bg->addComponent(ECS::Component::Flags::sprite, sprite);
    bg->addComponent(ECS::Component::Flags::transform, transform);
    bg->addComponent(ECS::Component::Flags::animation2D, animation);

    return bg;
}

void Game::Parallax::IA([[maybe_unused]] std::shared_ptr<ECS::Entity> &entity)
{

}
