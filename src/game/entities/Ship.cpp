/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Asteroid object
*/

#include "Ship.hpp"

std::shared_ptr<ECS::Entity> Game::ShipBeam::createEntity(std::shared_ptr<ECS::Entity> &parent)
{
    std::shared_ptr<ECS::Entity> newEntity(new ECS::Entity("Enemy"));
    Game::Rect rect(0, 0, 16, 16);
    auto parentTransform = static_cast<ECS::Component::Transform * >(parent->component(ECS::Component::Flags::transform).get());

    std::shared_ptr<ECS::IComponent> audio(new ECS::Component::Audio("bullet.mp3", false));
    std::shared_ptr<ECS::IComponent> damage(new ECS::Component::Damage(1));
    std::shared_ptr<ECS::IComponent> health(new ECS::Component::Health(1));
    std::shared_ptr<ECS::IComponent> script(new ECS::Component::Script(&ShipBeam::IA));
    std::shared_ptr<ECS::IComponent> sprite(new ECS::Component::Sprite("ressources/bullet.png", rect));
    std::shared_ptr<ECS::IComponent> speed(new ECS::Component::Speed(10));
    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform(parentTransform->x, parentTransform->y, parentTransform->z));
    std::shared_ptr<ECS::IComponent> collision(new ECS::Component::CollisionBox2D(0, 0, 16, 16));
    std::shared_ptr<ECS::IComponent> animation(new ECS::Component::Animation2D(std::chrono::milliseconds(50), rect, 116, 16.5));
    std::shared_ptr<ECS::IComponent> lifeSpan(new ECS::Component::LifeSpan(std::chrono::seconds(5), false));


    newEntity->addComponent(ECS::Component::Flags::audio, audio);
    newEntity->addComponent(ECS::Component::Flags::damage, damage);
    newEntity->addComponent(ECS::Component::Flags::health, health);
    newEntity->addComponent(ECS::Component::Flags::script, script);
    newEntity->addComponent(ECS::Component::Flags::sprite, sprite);
    newEntity->addComponent(ECS::Component::Flags::speed, speed);
    newEntity->addComponent(ECS::Component::Flags::transform, transform);
    newEntity->addComponent(ECS::Component::Flags::collisionBox2D, collision);
    newEntity->addComponent(ECS::Component::Flags::animation2D, animation);
    newEntity->addComponent(ECS::Component::Flags::lifeSpan, lifeSpan);
    return newEntity;
}

void Game::ShipBeam::IA(std::shared_ptr<ECS::Entity> &entity)
{
    if (!entity->hasComponent(ECS::Component::Flags::speed) || !entity->hasComponent(ECS::Component::Flags::transform))
        return;
    auto speed = static_cast<ECS::Component::Speed *>(entity->component(ECS::Component::Flags::speed).get());
    auto transform = static_cast<ECS::Component::Transform *>(entity->component(ECS::Component::Flags::transform).get());

    transform->x -= speed->speed;
    if (transform->x < 0)
        entity->deleteEntity();
}

ECS::Entity *Game::Ship::createEntity()
{
    ECS::Entity *newEntity = new ECS::Entity("Enemy");
    Game::Rect rect(0, 0, 34, 34);

    int random_variable = (std::rand() % 1060) + 20;

    std::shared_ptr<ECS::IComponent> audio(new ECS::Component::Audio("ship.mp3", false));
    std::shared_ptr<ECS::IComponent> damage(new ECS::Component::Damage(1));
    std::shared_ptr<ECS::IComponent> health(new ECS::Component::Health(1));
    std::shared_ptr<ECS::IComponent> script(new ECS::Component::Script(&Ship::IA));
    std::shared_ptr<ECS::IComponent> sprite(new ECS::Component::Sprite("ressources/ship.gif", rect));
    std::shared_ptr<ECS::IComponent> speed(new ECS::Component::Speed(5));
    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform(1920, random_variable, 0));
    std::shared_ptr<ECS::IComponent> collision(new ECS::Component::CollisionBox2D(0, 0, 50, 50));
    std::shared_ptr<ECS::IComponent> spawner(new ECS::Component::Spawner(std::chrono::seconds(2), &ShipBeam::createEntity));
    std::shared_ptr<ECS::IComponent> animation(new ECS::Component::Animation2D(std::chrono::milliseconds(100), rect, 232, 34));

    newEntity->addComponent(ECS::Component::Flags::audio, audio);
    newEntity->addComponent(ECS::Component::Flags::damage, damage);
    newEntity->addComponent(ECS::Component::Flags::health, health);
    newEntity->addComponent(ECS::Component::Flags::script, script);
    newEntity->addComponent(ECS::Component::Flags::sprite, sprite);
    newEntity->addComponent(ECS::Component::Flags::speed, speed);
    newEntity->addComponent(ECS::Component::Flags::transform, transform);
    newEntity->addComponent(ECS::Component::Flags::collisionBox2D, collision);
    newEntity->addComponent(ECS::Component::Flags::spawner, spawner);
    newEntity->addComponent(ECS::Component::Flags::animation2D, animation);
    return newEntity;
}

std::shared_ptr<ECS::Entity> Game::Ship::createEntityToSpawn(std::shared_ptr<ECS::Entity> &parent)
{
    Ship newShip;
    auto newEntity = newShip.createEntity();
    auto transformComponent = static_cast<ECS::Component::Transform *>(newEntity->component(ECS::Component::Flags::transform).get());
    auto transformComponentParent = static_cast<ECS::Component::Transform *>(parent->component(ECS::Component::Flags::transform).get());

    int random_variable = (std::rand() % 20) + transformComponentParent->y;
    transformComponent->y = random_variable;
    return std::shared_ptr<ECS::Entity>(newEntity);
}

void Game::Ship::IA(std::shared_ptr<ECS::Entity> &entity)
{
    static std::unordered_map<ECS::Entity *, float> _startingPoints;
    const float amp = 30;
    const float freq = 60;

    // Checking necessary components
    if (!entity->hasComponent(ECS::Component::Flags::speed) || !entity->hasComponent(ECS::Component::Flags::transform))
        return;

    // Getting all components
    auto speed = static_cast<ECS::Component::Speed *>(entity->component(ECS::Component::Flags::speed).get());
    auto transform = static_cast<ECS::Component::Transform *>(entity->component(ECS::Component::Flags::transform).get());

    // Getting the current transform
    if (_startingPoints.find(entity.get()) == _startingPoints.end())
        _startingPoints.emplace(entity.get(), transform->y);

    // Getting the current starting point
    float startPoint = _startingPoints[entity.get()];

    // Calculating y position (sin wave)
    transform->y = std::sin(transform->x / freq) * amp + startPoint;
    transform->x -= speed->speed;
    if (transform->x < 0)
        entity->deleteEntity();
}