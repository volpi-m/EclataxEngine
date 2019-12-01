/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** BeeSwarm
*/

#include "BeeSwarm.hpp"

extern "C" ECS::Entity *entryPoint()
{
    Game::BeeSwarm swarm;

    return swarm.createEntity();
}

ECS::Entity *Game::BeeSwarm::createEntity()
{
    ECS::Entity *swarm = new ECS::Entity("Enemy");
    Game::Rect rect(0, 0, 67, 64);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> randomSpawn(80, 1000);

    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform(1920, randomSpawn(gen), 0));
    std::shared_ptr<ECS::IComponent> speed(new ECS::Component::Speed(1));
    std::shared_ptr<ECS::IComponent> spawner(new ECS::Component::Spawner(std::chrono::seconds(1), &Bee::createEntityToSpawn));
    std::shared_ptr<ECS::IComponent> sprite(new ECS::Component::Sprite("ressources/swarm.png", rect));
    std::shared_ptr<ECS::IComponent> script(new ECS::Component::Script(&BeeSwarm::IA));
    std::shared_ptr<ECS::IComponent> animation(new ECS::Component::Animation2D(std::chrono::milliseconds(500), rect, 67 * 3, 67));
    std::shared_ptr<ECS::IComponent> collision(new ECS::Component::CollisionBox2D(0, 0, 80, 80));
    std::shared_ptr<ECS::IComponent> damage(new ECS::Component::Damage(1));
    std::shared_ptr<ECS::IComponent> health(new ECS::Component::Health(3));

    swarm->addComponent(ECS::Component::Flags::transform, transform);
    swarm->addComponent(ECS::Component::Flags::speed, speed);
    swarm->addComponent(ECS::Component::Flags::spawner, spawner);
    swarm->addComponent(ECS::Component::Flags::animation2D, animation);
    swarm->addComponent(ECS::Component::Flags::collisionBox2D, collision);
    swarm->addComponent(ECS::Component::Flags::sprite, sprite);
    swarm->addComponent(ECS::Component::Flags::damage, damage);
    swarm->addComponent(ECS::Component::Flags::health, health);
    swarm->addComponent(ECS::Component::Flags::script, script);

    return swarm;
}

void Game::BeeSwarm::IA(std::shared_ptr<ECS::Entity> &entity)
{
    auto transform = static_cast<ECS::Component::Transform *>(entity->component(ECS::Component::Flags::transform).get());
    auto speed = static_cast<ECS::Component::Speed *>(entity->component(ECS::Component::Flags::speed).get());
    float radius = 5;

    static float angle = 0;

    // rise angle value each frame
    angle += 0.05;

    // Compute coordinate of hive to draw a circular shape
    transform->x = transform->x - std::cos(angle) * radius - speed->speed;
    transform->y = transform->y + std::sin(angle) * radius;

    if (transform->x < 0)
        entity->deleteEntity();
}
