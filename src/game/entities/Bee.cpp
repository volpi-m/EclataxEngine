/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Bees
*/

#include "Bee.hpp"

ECS::Entity *Game::Bee::createEntity()
{
    ECS::Entity *newEntity = new ECS::Entity("Enemy");
    Game::Rect rect(0, 0, 33, 34);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> randomSpawn(20, 1060);

    std::shared_ptr<ECS::IComponent> audio(new ECS::Component::Audio("ship.mp3", false));
    std::shared_ptr<ECS::IComponent> damage(new ECS::Component::Damage(1));
    std::shared_ptr<ECS::IComponent> health(new ECS::Component::Health(1));
    std::shared_ptr<ECS::IComponent> script(new ECS::Component::Script(&Bee::IA));
    std::shared_ptr<ECS::IComponent> sprite(new ECS::Component::Sprite("ressources/bees.png", rect));
    std::shared_ptr<ECS::IComponent> speed(new ECS::Component::Speed(7));
    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform(1920, randomSpawn(gen), 0));
    std::shared_ptr<ECS::IComponent> collision(new ECS::Component::CollisionBox2D(0, 0, 50, 50));
    std::shared_ptr<ECS::IComponent> animation(new ECS::Component::Animation2D(std::chrono::milliseconds(100), rect, 495, 33));

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

std::shared_ptr<ECS::Entity> Game::Bee::createEntityToSpawn(std::shared_ptr<ECS::Entity> &parent)
{
    Bee newBee;
    auto newEntity = newBee.createEntity();
    auto transform = static_cast<ECS::Component::Transform *>(newEntity->component(ECS::Component::Flags::transform).get());
    auto transformParent = static_cast<ECS::Component::Transform *>(parent->component(ECS::Component::Flags::transform).get());

    transform->y = std::rand() % 20 + transformParent->y;
    transform->x = transformParent->x;
    return std::shared_ptr<ECS::Entity>(newEntity);
}

void Game::Bee::IA(std::shared_ptr<ECS::Entity> &entity)
{
    auto speed = static_cast<ECS::Component::Speed *>(entity->component(ECS::Component::Flags::speed).get());
    auto transform = static_cast<ECS::Component::Transform *>(entity->component(ECS::Component::Flags::transform).get());

    transform->x -= speed->speed;
    if (transform->x < 0)
        entity->deleteEntity();
}
