/*
** EPITECH PROJECT, 2019
** R-Type
** File description:
** Asteroid object
*/

#include "Fleet.hpp"

extern "C" ECS::Entity *entryPoint()
{
    Game::Fleet fleet;

    return fleet.createEntity();
}

ECS::Entity *Game::Fleet::createEntity()
{
    ECS::Entity *newEntity = new ECS::Entity("Spawner");
    int random_variable = (std::rand() % 1060) + 20;

    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform(1920, random_variable, 0));
    std::shared_ptr<ECS::IComponent> spawner(new ECS::Component::Spawner(std::chrono::seconds(1), &Ship::createEntityToSpawn));
    std::shared_ptr<ECS::IComponent> lifeSpan(new ECS::Component::LifeSpan(std::chrono::seconds(5), false));

    newEntity->addComponent(ECS::Component::Flags::transform, transform);
    newEntity->addComponent(ECS::Component::Flags::spawner, spawner);
    newEntity->addComponent(ECS::Component::Flags::lifeSpan, lifeSpan);
    return newEntity;
}