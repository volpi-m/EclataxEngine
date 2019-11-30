/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Player
*/

#include "Player.hpp"

extern "C" ECS::Entity *entryPoint()
{
    Game::Player player;

    return player.createEntity();
}

ECS::Entity *Game::Player::createEntity()
{
    ECS::Entity *newEntity = new ECS::Entity("Enemy Ship");
    Game::Rect rect(0, 0, 34, 34);

    std::shared_ptr<ECS::IComponent> audio(new ECS::Component::Audio("ship.mp3", false));
    std::shared_ptr<ECS::IComponent> damage(new ECS::Component::Damage(1));
    std::shared_ptr<ECS::IComponent> health(new ECS::Component::Health(1));
    std::shared_ptr<ECS::IComponent> script(new ECS::Component::Script(&Player::IA));
    std::shared_ptr<ECS::IComponent> sprite(new ECS::Component::Sprite("ressources/ship.gif", rect));
    std::shared_ptr<ECS::IComponent> speed(new ECS::Component::Speed(2));
    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform(1920, 600, 0));
    std::shared_ptr<ECS::IComponent> collision(new ECS::Component::CollisionBox2D(0, 0, 50, 50));
    std::shared_ptr<ECS::IComponent> animation(new ECS::Component::Animation2D(std::chrono::milliseconds(100), rect, 232, 34));

    newEntity->addComponent(ECS::Component::Flags::audio, audio);
    newEntity->addComponent(ECS::Component::Flags::damage, damage);
    newEntity->addComponent(ECS::Component::Flags::health, health);
    newEntity->addComponent(ECS::Component::Flags::script, script);
    newEntity->addComponent(ECS::Component::Flags::sprite, sprite);
    newEntity->addComponent(ECS::Component::Flags::speed, speed);
    newEntity->addComponent(ECS::Component::Flags::transform, transform);
    newEntity->addComponent(ECS::Component::Flags::collisionBox2D, collision);
    newEntity->addComponent(ECS::Component::Flags::animation2D, animation);
    return newEntity;
}

void Game::Player::IA(std::shared_ptr<ECS::Entity> &entity)
{

}
