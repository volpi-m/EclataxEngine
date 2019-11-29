/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Asteroid object
*/

#include "Ship.hpp"

extern "C" ECS::Entity *entryPoint()
{
    Game::Ship ship;

    return ship.createEntity();
}

std::shared_ptr<ECS::Entity> Game::ShipBeam::createEntity(std::shared_ptr<ECS::Entity> &parent)
{
    std::shared_ptr<ECS::Entity> newEntity(new ECS::Entity("Enemy Bullet"));
    Game::Rect rect(0, 0, 32, 32);
    auto parentTransform = static_cast<ECS::Component::Transform * >(parent->component(ECS::Component::Flags::transform).get());

    std::shared_ptr<ECS::IComponent> audio(new ECS::Component::Audio("bullet.mp3", false));
    std::shared_ptr<ECS::IComponent> damage(new ECS::Component::Damage(20));
    std::shared_ptr<ECS::IComponent> health(new ECS::Component::Health(1));
    std::shared_ptr<ECS::IComponent> script(new ECS::Component::Script(&ShipBeam::IA));
    std::shared_ptr<ECS::IComponent> sprite(new ECS::Component::Sprite("bullet.png", rect));
    std::shared_ptr<ECS::IComponent> speed(new ECS::Component::Speed(5));
    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform(parentTransform->x, parentTransform->y, parentTransform->z));
    std::shared_ptr<ECS::IComponent> collision(new ECS::Component::CollisionBox2D(0, 0, 20, 20));

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

void Game::ShipBeam::IA(std::shared_ptr<ECS::Entity> &entity)
{
    auto speed = static_cast<ECS::Component::Speed *>(entity->component(ECS::Component::Flags::speed).get());
    auto transform = static_cast<ECS::Component::Transform *>(entity->component(ECS::Component::Flags::transform).get());

    transform->x -= speed->speed;
}

ECS::Entity *Game::Ship::createEntity()
{
    ECS::Entity *newEntity = new ECS::Entity("Enemy Ship");
    Game::Rect rect(0, 0, 32, 32);

    std::shared_ptr<ECS::IComponent> audio(new ECS::Component::Audio("ship.mp3", false));
    std::shared_ptr<ECS::IComponent> damage(new ECS::Component::Damage(1));
    std::shared_ptr<ECS::IComponent> health(new ECS::Component::Health(1));
    std::shared_ptr<ECS::IComponent> script(new ECS::Component::Script(&Ship::IA));
    std::shared_ptr<ECS::IComponent> sprite(new ECS::Component::Sprite("ship.png", rect));
    std::shared_ptr<ECS::IComponent> speed(new ECS::Component::Speed(0.01));
    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform(960, 0, 0));
    std::shared_ptr<ECS::IComponent> collision(new ECS::Component::CollisionBox2D(0, 0, 50, 50));
    std::shared_ptr<ECS::IComponent> spawner(new ECS::Component::Spawner(std::chrono::seconds(2), &ShipBeam::createEntity));

    newEntity->addComponent(ECS::Component::Flags::audio, audio);
    newEntity->addComponent(ECS::Component::Flags::damage, damage);
    newEntity->addComponent(ECS::Component::Flags::health, health);
    newEntity->addComponent(ECS::Component::Flags::script, script);
    newEntity->addComponent(ECS::Component::Flags::sprite, sprite);
    newEntity->addComponent(ECS::Component::Flags::speed, speed);
    newEntity->addComponent(ECS::Component::Flags::transform, transform);
    newEntity->addComponent(ECS::Component::Flags::collisionBox2D, collision);
    newEntity->addComponent(ECS::Component::Flags::spawner, spawner);
    return newEntity;
}

void Game::Ship::IA(std::shared_ptr<ECS::Entity> &entity)
{
    const float amp = 20;
    const float freq = 60;
    auto speed = static_cast<ECS::Component::Speed *>(entity->component(ECS::Component::Flags::speed).get());
    auto transform = static_cast<ECS::Component::Transform *>(entity->component(ECS::Component::Flags::transform).get());

    transform->y = std::sin(transform->x / freq) * amp;
    transform->x -= speed->speed;

    // USE THE SCRIPT TO SEE IF THE CHILDREN ENTITIES (BULLETS) NEEDS TO BE DELETED
    std::cout << std::endl << "----------------------------" << std::endl;
    std::cout << "space ship y : " << transform->y << std::endl;
    std::cout << "space ship x : " << transform->x << std::endl;
    std::cout << "----------------------------" << std::endl;
}