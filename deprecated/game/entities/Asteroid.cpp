/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Asteroid object
*/

#include "Asteroid.hpp"

extern "C" ECS::Entity *entryPoint()
{
    Game::Asteroid asteroid;

    return asteroid.createEntity();
}

ECS::Entity *Game::Asteroid::createEntity()
{
    ECS::Entity *newEntity = new ECS::Entity("Enemy");
    Game::Rect rect(0, 0, 32, 32);
    std::shared_ptr<ECS::IComponent> audio(new ECS::Component::Audio("asteriod.mp3", false));
    std::shared_ptr<ECS::IComponent> damage(new ECS::Component::Damage(15));
    std::shared_ptr<ECS::IComponent> health(new ECS::Component::Health(1));
    std::shared_ptr<ECS::IComponent> script(new ECS::Component::Script(&Asteroid::IA));
    std::shared_ptr<ECS::IComponent> sprite(new ECS::Component::Sprite("asteriod.png", rect));
    std::shared_ptr<ECS::IComponent> speed(new ECS::Component::Speed(2));
    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform(960, 0, 0));
    std::shared_ptr<ECS::IComponent> particules(new ECS::Component::Particules);
    std::shared_ptr<ECS::IComponent> acceleration(new ECS::Component::Acceleration(1));
    std::shared_ptr<ECS::IComponent> collision(new ECS::Component::CollisionBox2D(0, 0, 50, 50));

    newEntity->addComponent(ECS::Component::Flags::audio, audio);
    newEntity->addComponent(ECS::Component::Flags::damage, damage);
    newEntity->addComponent(ECS::Component::Flags::health, health);
    newEntity->addComponent(ECS::Component::Flags::script, script);
    newEntity->addComponent(ECS::Component::Flags::sprite, sprite);
    newEntity->addComponent(ECS::Component::Flags::speed, speed);
    newEntity->addComponent(ECS::Component::Flags::transform, transform);
    newEntity->addComponent(ECS::Component::Flags::particules, particules);
    newEntity->addComponent(ECS::Component::Flags::acceleration, acceleration);
    newEntity->addComponent(ECS::Component::Flags::collisionBox2D, collision);
    return newEntity;
}

void Game::Asteroid::IA(std::shared_ptr<ECS::Entity> &entity)
{
    auto speed = static_cast<ECS::Component::Speed *>(entity->component(ECS::Component::Flags::speed).get());
    auto transform = static_cast<ECS::Component::Transform *>(entity->component(ECS::Component::Flags::transform).get());
    auto acceleration = static_cast<ECS::Component::Acceleration *>(entity->component(ECS::Component::Flags::acceleration).get());

    transform->x -= speed->speed * acceleration->acceleration;
    acceleration->acceleration += 0.1;

    std::cout << "------------------------------------------" << std::endl;
    std::cout << "current asteriod speed : " << speed->speed << std::endl;
    std::cout << "current asteriod x : " << transform->x << std::endl;
}