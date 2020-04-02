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

std::shared_ptr<ECS::Entity> Game::PlayerShipBeam::createEntity(std::shared_ptr<ECS::Entity> &parent)
{
    std::shared_ptr<ECS::Entity> newEntity(new ECS::Entity("Player Bullet"));
    Game::Rect rect(0, 0, 18, 8);
    auto parentTransform = static_cast<ECS::Component::Transform * >(parent->component(ECS::Component::Flags::transform).get());

    std::shared_ptr<ECS::IComponent> audio(new ECS::Component::Audio("bullet.mp3", false));
    std::shared_ptr<ECS::IComponent> damage(new ECS::Component::Damage(1));
    std::shared_ptr<ECS::IComponent> health(new ECS::Component::Health(1));
    std::shared_ptr<ECS::IComponent> script(new ECS::Component::Script(&PlayerShipBeam::IA));
    std::shared_ptr<ECS::IComponent> sprite(new ECS::Component::Sprite("ressources/playerShipBullet.png", rect));
    std::shared_ptr<ECS::IComponent> speed(new ECS::Component::Speed(20));
    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform(parentTransform->x, parentTransform->y, parentTransform->z));
    std::shared_ptr<ECS::IComponent> collision(new ECS::Component::CollisionBox2D(0, 0, 18, 8));

    newEntity->addComponent(ECS::Component::Flags::audio, audio);
    newEntity->addComponent(ECS::Component::Flags::damage, damage);
    newEntity->addComponent(ECS::Component::Flags::health, health);
    newEntity->addComponent(ECS::Component::Flags::script, script);
    newEntity->addComponent(ECS::Component::Flags::sprite, sprite);
    newEntity->addComponent(ECS::Component::Flags::speed, speed);
    newEntity->addComponent(ECS::Component::Flags::transform, transform);
    newEntity->addComponent(ECS::Component::Flags::collisionBox2D, collision);
    return newEntity;
}

void Game::PlayerShipBeam::IA(std::shared_ptr<ECS::Entity> &entity)
{
    auto speed = static_cast<ECS::Component::Speed *>(entity->component(ECS::Component::Flags::speed).get());
    auto transform = static_cast<ECS::Component::Transform *>(entity->component(ECS::Component::Flags::transform).get());

    if (transform->x >= 1920)
        entity->deleteEntity();
    transform->x += speed->speed;
}

ECS::Entity *Game::Player::createEntity()
{
    ECS::Entity *newEntity = new ECS::Entity("Player");
    Game::Rect rect(0, 0, 33, 18);

    std::shared_ptr<ECS::IComponent> audio(new ECS::Component::Audio("ship.mp3", false));
    std::shared_ptr<ECS::IComponent> health(new ECS::Component::Health(1));
    std::shared_ptr<ECS::IComponent> damage(new ECS::Component::Damage(1));
    std::shared_ptr<ECS::IComponent> sprite(new ECS::Component::Sprite("ressources/player.png", rect));
    std::shared_ptr<ECS::IComponent> speed(new ECS::Component::Speed(5));
    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform(100, 600, 0));
    std::shared_ptr<ECS::IComponent> collision(new ECS::Component::CollisionBox2D(0, 0, 33, 18));
    std::shared_ptr<ECS::IComponent> spawner(new ECS::Component::Spawner(std::chrono::seconds(0), &PlayerShipBeam::createEntity));
    std::shared_ptr<ECS::IComponent> script(new ECS::Component::Script(&Player::IA));

    newEntity->addComponent(ECS::Component::Flags::audio, audio);
    newEntity->addComponent(ECS::Component::Flags::health, health);
    newEntity->addComponent(ECS::Component::Flags::damage, damage);
    newEntity->addComponent(ECS::Component::Flags::sprite, sprite);
    newEntity->addComponent(ECS::Component::Flags::speed, speed);
    newEntity->addComponent(ECS::Component::Flags::transform, transform);
    newEntity->addComponent(ECS::Component::Flags::collisionBox2D, collision);
    newEntity->addComponent(ECS::Component::Flags::spawner, spawner);
    newEntity->addComponent(ECS::Component::Flags::script, script);
    return newEntity;
}

void Game::Player::IA(std::shared_ptr<ECS::Entity> &entity)
{
    auto transform = static_cast<ECS::Component::Transform *>(entity->component(ECS::Component::Flags::transform).get());

    if (transform->x < 0)
        transform->x = 0;
    if (transform->y < 0)
        transform->y = 0;
    if (transform->x > 1887)
        transform->x = 1887;
    if (transform->y > 1062)
        transform->y = 1062;
}
