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
    l->generateDebugMessage(Debug::type::INFO , "Starting Level 1", "Level1Scene::constructor()");
    initComponents();
}

Scenes::Level1Scene::Level1Scene(const char *name, std::shared_ptr<Module::EntityComponentSystem> &ECS, int player) : AScene(name, ECS, player)
{
    Debug::Logger *l = Debug::Logger::getInstance();
    l->generateDebugMessage(Debug::type::INFO , "Starting Level 1", "Level1Scene::constructor()");
    initComponents();
}

Scenes::Level1Scene::Level1Scene(int player, const std::string &name) : AScene(player, name) {}

Scenes::Level1Scene::Level1Scene(int player, const char *name) : AScene(player, name) {}

Scenes::IScene *Scenes::Level1Scene::run()
{
    auto collisionSystem = static_cast<ECS::System::CollisionSystem *>(_ECS->system(ECS::System::Flags::Collision).get());

    if (!alivePlayers()) {
        _pop = true;
        return nullptr;
    }

    // Chceking collisions
    for (unsigned long long item1 = 0; item1 < _ids.size() && _ECS->hasEntity(_ids[item1]); ++item1)
        for (unsigned long long item2 = 0; item2 < _ids.size() && _ECS->hasEntity(_ids[item2]); ++item2)
            checkCollisionTags(_ECS->entity(_ids[item1]), _ECS->entity(_ids[item2]), collisionSystem);

    // Updating systems
    _ECS->update();

    // Pushing entities to the stack
    for (unsigned long long id = 0; id < _ids.size() && _ECS->hasEntity(_ids[id]); ++id)
        pushEntityStack(_ECS->entity(_ids[id]), _ids[id]);

    // Clearing deleted entities
    _ECS->clearEntities();
    _ids = _ECS->ids();
    return nullptr;
}

void Scenes::Level1Scene::checkCollisionTags(std::shared_ptr<ECS::Entity> &first, std::shared_ptr<ECS::Entity> &second, ECS::System::CollisionSystem *collisionSystem)
{
    if (first->tag() == second->tag())
        return;
    if ((first->tag() == "Player" && second->tag() == "Player Bullet") ||
    (second->tag() == "Player" && first->tag() == "Player Bullet"))
        return;
    collisionSystem->onCollideDamage2D(first, second);
}

bool Scenes::Level1Scene::alivePlayers()
{
    for (auto id : _ids)
        if (_ECS->entity(id)->tag() == "Player")
            return true;
    return false;
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
    std::shared_ptr<ECS::ISystem> systemIA(new ECS::System::IASystem);
    std::shared_ptr<ECS::ISystem> systemAnimation(new ECS::System::AnimationSystem);
    std::shared_ptr<ECS::ISystem> systemMovement(new ECS::System::MovementSystem);
    std::shared_ptr<ECS::ISystem> systemSpawn(new ECS::System::SpawnerSystem);
    std::shared_ptr<ECS::ISystem> systemLifeSpan(new ECS::System::LifeSpanSystem);
    std::shared_ptr<ECS::ISystem> systemHealthManipulator(new ECS::System::HealthManipulator);
    std::shared_ptr<ECS::ISystem> systemCollisionSystem(new ECS::System::CollisionSystem);

    std::shared_ptr<ECS::IComponent> sprite(new ECS::Component::Sprite("ressources/level_1.jpg", Game::Rect(0, 0, 1920, 1080)));
    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform);

    _ids.push_back(_ECS->createEntity("Background"));
    for (int i = 0; i < _players; ++i)
        _ids.push_back(_ECS->createEntityFromLibrary("lib/libplayer.so"));
    _ids.push_back(_ECS->createEntityFromLibrary("lib/libfleet.so"));

    _ECS->addComponentToEntity(_ids.front(), ECS::Component::Flags::sprite, sprite);
    _ECS->addComponentToEntity(_ids.front(), ECS::Component::Flags::transform, transform);

    _ECS->addSystem(ECS::System::Flags::IA, systemIA);
    _ECS->addSystem(ECS::System::Flags::Animation, systemAnimation);
    _ECS->addSystem(ECS::System::Flags::Movement, systemMovement);
    _ECS->addSystem(ECS::System::Flags::Spawner, systemSpawn);
    _ECS->addSystem(ECS::System::Flags::LifeSpan, systemLifeSpan);
    _ECS->addSystem(ECS::System::Flags::HealthManipulator, systemHealthManipulator);
    _ECS->addSystem(ECS::System::Flags::Collision, systemCollisionSystem);
    _ids = _ECS->ids();
}

void Scenes::Level1Scene::handleEvent(std::queue<std::pair<int, size_t>> &events)
{
    auto movementSystem = static_cast<ECS::System::MovementSystem *>(_ECS->system(ECS::System::Flags::Movement).get());
    static std::chrono::high_resolution_clock::time_point lastShot[4] = {std::chrono::high_resolution_clock::now(),
    std::chrono::high_resolution_clock::now(), std::chrono::high_resolution_clock::now(), std::chrono::high_resolution_clock::now()};
    float speeds[4];

    // Getting the current speed of all players
    getPlayersSpeed(speeds, movementSystem);
    while (!events.empty()) {

        // std::cout << "player: " << events.front().first << ", event: " << events.front().second << std::endl; 
        
        // Checking inputs from the player that sent the packet
        if (!_ECS->hasEntity(_ids.at(events.front().first))) {
            events.pop();
            continue;
        }
        auto sps = _ECS->entity(_ids.at(events.front().first));
        float x = 0;
        float y = 0;
        if (events.front().second & UP)
            y -= 2;
        else if (events.front().second & DOWN)
            y += 2;
        if (events.front().second & LEFT)
            x -= 2;
        else if (events.front().second & RIGHT)
            x += 2;
        if (events.front().second & SPACE)
            computeShots(sps, lastShot[events.front().first - 1]);
        
        // Moving the player of needed
        movementSystem->move(sps, x * speeds[events.front().first - 1], y * speeds[events.front().first - 1], 0);
        events.pop();
    }
}

void Scenes::Level1Scene::computeShots(std::shared_ptr<ECS::Entity> &entity, std::chrono::high_resolution_clock::time_point &lastShot)
{
    static const auto fireRate = std::chrono::milliseconds(400);
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();

    // Checking if the player as shoot 1/2 second beforehand
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastShot).count() > fireRate.count()) {
        
        auto spawnerSystem = static_cast<ECS::System::SpawnerSystem *>(_ECS->system(ECS::System::Flags::Spawner).get());
        
        spawnerSystem->spawn(entity, _ECS);
        lastShot = now;
    }
}

void Scenes::Level1Scene::getPlayersSpeed(float *speeds, ECS::System::MovementSystem *movementSystem)
{
    // getting the speed of all players
    for (int i = 0; i < _players; ++i)
        if (_ECS->hasEntity(_ids[i + 1]) && _ECS->entity(_ids[i + 1])->tag() == "Player")
            speeds[i] = movementSystem->speed(_ECS->entity(_ids[i + 1]));
}