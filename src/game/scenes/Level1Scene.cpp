/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** splash screen
*/

#include "Level1Scene.hpp"

Scenes::Level1Scene::Level1Scene(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS, int player) : AScene(name, ECS, player)
{
    Debug::Logger *l = Debug::Logger::getInstance();
    l->generateDebugMessage(Debug::type::INFO , "Let's build a wall !", "Level1Scene::constructor()");
    initComponents();
}

Scenes::Level1Scene::Level1Scene(const char *name, std::shared_ptr<Module::EntityComponentSystem> &ECS, int player) : AScene(name, ECS, player)
{
    Debug::Logger *l = Debug::Logger::getInstance();
    l->generateDebugMessage(Debug::type::INFO , "Let's build a wall !", "Level1Scene::constructor()");
    initComponents();
}

Scenes::Level1Scene::Level1Scene(int player, const std::string &name) : AScene(player, name) {}

Scenes::Level1Scene::Level1Scene(int player, const char *name) : AScene(player, name) {}

Scenes::IScene *Scenes::Level1Scene::run()
{
    _ids = _ECS->ids();
    _ECS->update();
    for (unsigned long long id = 0; id < _ids.size() && _ECS->hasEntity(_ids[id]); ++id)
        pushEntityStack(_ECS->entity(_ids[id]), _ids[id]);
    _ECS->clearEntities();
    return nullptr;
}

void Scenes::Level1Scene::setVisible(bool state)
{
    for (auto &id : _ids)
        _ECS->setEntityVisibleState(id, state);
}

void Scenes::Level1Scene::remove()
{
    for (auto &id : _ids)
        _ECS->deleteEntity(id);
}

void Scenes::Level1Scene::initComponents()
{
    std::unique_ptr<ECS::ISystem> systemIA(new ECS::System::IASystem);
    std::unique_ptr<ECS::ISystem> systemAnimation(new ECS::System::AnimationSystem);
    std::unique_ptr<ECS::ISystem> systemMovement(new ECS::System::MovementSystem);
    std::unique_ptr<ECS::ISystem> systemSpawn(new ECS::System::SpawnerSystem);
    std::unique_ptr<ECS::ISystem> systemLifeSpan(new ECS::System::LifeSpanSystem);

    std::shared_ptr<ECS::IComponent> sprite(new ECS::Component::Sprite("ressources/level_1.jpg", Game::Rect(0, 0, 1920, 1080)));
    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform);

    _ids.push_back(_ECS->createEntity("Background"));
    _ids.push_back(_ECS->createEntityFromLibrary("lib/libplayer.so"));
    _ids.push_back(_ECS->createEntityFromLibrary("lib/libfleet.so"));

    _ECS->addComponentToEntity(_ids.front(), ECS::Component::Flags::sprite, sprite);
    _ECS->addComponentToEntity(_ids.front(), ECS::Component::Flags::transform, transform);

    _ECS->addSystem(ECS::System::Flags::IA, systemIA);
    _ECS->addSystem(ECS::System::Flags::Animation, systemAnimation);
    _ECS->addSystem(ECS::System::Flags::Movement, systemMovement);
    _ECS->addSystem(ECS::System::Flags::Spawner, systemSpawn);
    _ECS->addSystem(ECS::System::Flags::LifeSpan, systemLifeSpan);
}

void Scenes::Level1Scene::handleEvent(std::queue<std::pair<int, size_t>> &events)
{
    auto sps = _ECS->entity(_ids.at(1));
    auto movementSystem = static_cast<ECS::System::MovementSystem *>(_ECS->system(ECS::System::Flags::Movement).get());
    static std::chrono::high_resolution_clock::time_point lastShot = std::chrono::high_resolution_clock::now();
    static auto fireRate = std::chrono::milliseconds(400);
    float speed = movementSystem->speed(sps);
    float x = 0;
    float y = 0;

    while (!events.empty()) {
        if (events.front().second & UP)
            y -= 2;
        else if (events.front().second & DOWN)
            y += 2;
        if (events.front().second & LEFT)
            x -= 2;
        else if (events.front().second & RIGHT)
            x += 2;
        if (events.front().second & SPACE) {
            std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();

            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastShot).count() > fireRate.count()) {
                auto spawnerSystem = static_cast<ECS::System::SpawnerSystem *>(_ECS->system(ECS::System::Flags::Spawner).get());

                spawnerSystem->spawn(sps, _ECS);
                lastShot = now;
            }
        }
        movementSystem->move(sps, x * speed, y * speed, 0);
        events.pop();
    }
}