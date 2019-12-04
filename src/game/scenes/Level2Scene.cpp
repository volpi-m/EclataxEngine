/*
** EPITECH PROJECT, 2019
** Rtype
** File description:
** splash screen
*/

#include "Level2Scene.hpp"

Scenes::Level2Scene::Level2Scene(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS, int player) : AScene(name, ECS, player)
{
    Debug::Logger *l = Debug::Logger::getInstance();
    l->generateDebugMessage(Debug::type::INFO , "Starting Level 2", "Level2Scene::constructor()");

    _waves.push_back(&Level2Scene::waveOne);
    _waves.push_back(&Level2Scene::waveTwo);
    _waves.push_back(&Level2Scene::waveThree);
    _waves.push_back(&Level2Scene::waveFour);

    initComponents();
}

Scenes::Level2Scene::Level2Scene(const char *name, std::shared_ptr<Module::EntityComponentSystem> &ECS, int player) : AScene(name, ECS, player)
{
    Debug::Logger *l = Debug::Logger::getInstance();
    l->generateDebugMessage(Debug::type::INFO , "Starting Level 2", "Level2Scene::constructor()");

    _waves.push_back(&Level2Scene::waveOne);
    _waves.push_back(&Level2Scene::waveTwo);
    _waves.push_back(&Level2Scene::waveThree);
    _waves.push_back(&Level2Scene::waveFour);

    initComponents();
}

Scenes::Level2Scene::Level2Scene(int player, const std::string &name) : AScene(player, name) {}

Scenes::Level2Scene::Level2Scene(int player, const char *name) : AScene(player, name) {}

Scenes::IScene *Scenes::Level2Scene::run()
{
    auto collisionSystem = static_cast<ECS::System::CollisionSystem *>(_ECS->system(ECS::System::Flags::Collision).get());

    // Changing the current wave if needed
    changeWave();

    // Checking if all player are alive or that the hit the final wave
    if (!alivePlayers() || _currentWave > _MaxWaves) {
        remove();
        _pop = true;
        _swap = true;
        _name = "Hub scene";
        _ECS->clear();
        return nullptr;
    }

    // Checking collisions
    for (unsigned long long item1 = 0; item1 < _ids.size() && _ECS->hasEntity(_ids[item1]); ++item1)
        for (unsigned long long item2 = item1; item2 < _ids.size() && _ECS->hasEntity(_ids[item2]); ++item2)
            checkCollisionTags(_ECS->entity(_ids[item1]), _ECS->entity(_ids[item2]), collisionSystem);

    // Updating systems
    _ECS->update();

    // Pushing entities to the stack
    _ids = _ECS->ids();
    //std::cout << "entities on screen: " << _ids.size() << std::endl;
    for (unsigned long long id = 0; id < _ids.size(); ++id)
        pushEntityStack(_ECS->entity(_ids[id]), _ids[id]);

    // Clearing deleted entities
    _ECS->clearEntities();
    _ids = _ECS->ids();
    return nullptr;
}

void Scenes::Level2Scene::changeWave()
{
    // Checking if the current wave needs to be changed
    _ids = _ECS->ids();
    for (unsigned long long item = 0; item < _ids.size() && _ECS->hasEntity(_ids[item]); ++item)
        if (_ECS->entity(_ids[item])->tag() == "Enemy" || _ECS->entity(_ids[item])->tag() == "Spawner")
            return;

    // Changing wave
    _currentWave += 1;
    if (_currentWave <= _MaxWaves) {
        Debug::Logger *log = Debug::Logger::getInstance();

        log->generateDebugMessage(Debug::INFO, "Player are currently on wave " + std::to_string(_currentWave), "Scenes::Level2Scene::changeWave");
        _waves.at(_currentWave)(*this);
    }
    _ids = _ECS->ids();
}

void Scenes::Level2Scene::checkCollisionTags(std::shared_ptr<ECS::Entity> &first, std::shared_ptr<ECS::Entity> &second, ECS::System::CollisionSystem *collisionSystem)
{
    if (first->tag() == second->tag())
        return;
    if ((first->tag() == "Player" && second->tag() == "Player Bullet") ||
    (second->tag() == "Player" && first->tag() == "Player Bullet"))
        return;
    collisionSystem->onCollideDamage2D(first, second);
}

bool Scenes::Level2Scene::alivePlayers()
{
    for (auto id : _ids)
        if (_ECS->entity(id)->tag() == "Player")
            return true;
    return false;
}

void Scenes::Level2Scene::setVisible(bool state)
{
    for (auto &id : _ids)
        _ECS->setEntityVisibleState(id, state);
}

void Scenes::Level2Scene::remove()
{
    for (auto &id : _ids)
        _ECS->deleteEntity(id);
    _ids = _ECS->ids();
    for (unsigned long long id = 0; id < _ids.size(); ++id)
        pushEntityStack(_ECS->entity(_ids[id]), _ids[id]);
    _ECS->clearEntities();
}

void Scenes::Level2Scene::initComponents()
{
    std::shared_ptr<ECS::ISystem> systemIA(new ECS::System::IASystem);
    std::shared_ptr<ECS::ISystem> systemAnimation(new ECS::System::AnimationSystem);
    std::shared_ptr<ECS::ISystem> systemMovement(new ECS::System::MovementSystem);
    std::shared_ptr<ECS::ISystem> systemSpawn(new ECS::System::SpawnerSystem);
    std::shared_ptr<ECS::ISystem> systemLifeSpan(new ECS::System::LifeSpanSystem);
    std::shared_ptr<ECS::ISystem> systemHealthManipulator(new ECS::System::HealthManipulator);
    std::shared_ptr<ECS::ISystem> systemCollisionSystem(new ECS::System::CollisionSystem);

    _ECS->createEntityFromLibrary("lib/libparallaxalt.so");
    for (int i = 1; i <= _players; ++i) {
        auto newId = _ECS->createEntityFromLibrary("lib/libplayer.so");
        if (newId)
            _playersIds.emplace(i, newId);
    }
    _ids = _ECS->ids();
    _waves.at(0)(*this);

    _ECS->addSystem(ECS::System::Flags::Collision, systemCollisionSystem);
    _ECS->addSystem(ECS::System::Flags::IA, systemIA);
    _ECS->addSystem(ECS::System::Flags::Animation, systemAnimation);
    _ECS->addSystem(ECS::System::Flags::Movement, systemMovement);
    _ECS->addSystem(ECS::System::Flags::Spawner, systemSpawn);
    _ECS->addSystem(ECS::System::Flags::LifeSpan, systemLifeSpan);
    _ECS->addSystem(ECS::System::Flags::HealthManipulator, systemHealthManipulator);
}

void Scenes::Level2Scene::handleEvent(std::queue<std::pair<int, size_t>> events)
{
    auto movementSystem = static_cast<ECS::System::MovementSystem *>(_ECS->system(ECS::System::Flags::Movement).get());
    static std::chrono::high_resolution_clock::time_point lastShot[4] = {std::chrono::high_resolution_clock::now(),
    std::chrono::high_resolution_clock::now(), std::chrono::high_resolution_clock::now(), std::chrono::high_resolution_clock::now()};
    float speeds[4];

    // Getting the current speed of all players
    getPlayersSpeed(speeds, movementSystem);
    while (!events.empty()) {

        // Checking inputs from the player that sent the packet
        if (!checkPlayer(events.front())) {
            events.pop();
            continue;
        }
        auto sps = _ECS->entity(_playersIds[events.front().first]);
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
        else if (events.front().second & ESCAPE) {
            sps->deleteEntity();
            pushEntityStack(sps, _playersIds[events.front().first]);
        }
        if (events.front().second & SPACE)
            computeShots(sps, lastShot[events.front().first - 1]);

        // Moving the player of needed
        movementSystem->move(sps, x * speeds[events.front().first - 1], y * speeds[events.front().first - 1], 0);
        events.pop();
    }
}

bool Scenes::Level2Scene::checkPlayer(std::pair<int, std::size_t> &key)
{
    for (auto id : _playersIds)
        if (id.first == key.first && _ECS->hasEntity(_playersIds[key.first]))
            return true;
    return false;
}

void Scenes::Level2Scene::computeShots(std::shared_ptr<ECS::Entity> &entity, std::chrono::high_resolution_clock::time_point &lastShot)
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

void Scenes::Level2Scene::getPlayersSpeed(float *speeds, ECS::System::MovementSystem *movementSystem)
{
    // getting the speed of all players
    for (int i = 0; i < _players; ++i)
        if (i + 1 < (int)_ids.size() && _ECS->hasEntity(_ids[i + 1]) && _ECS->entity(_ids[i + 1])->tag() == "Player")
            speeds[i] = movementSystem->speed(_ECS->entity(_ids[i + 1]));
}

void Scenes::Level2Scene::waveOne()
{
    // Creating fleets
    _ECS->createEntityFromLibrary("lib/libbee.so");
    _ECS->createEntityFromLibrary("lib/libbee.so");
    _ECS->createEntityFromLibrary("lib/libswarm.so");
    _ids = _ECS->ids();
}

void Scenes::Level2Scene::waveTwo()
{
    // Spawning small ships
    _ECS->createEntityFromLibrary("lib/libfleet.so");
    _ECS->createEntityFromLibrary("lib/libfleet.so");
    _ECS->createEntityFromLibrary("lib/libfleet.so");
}

void Scenes::Level2Scene::waveThree()
{
    // Spawning swarms
    _ECS->createEntityFromLibrary("lib/libswarm.so");
    _ECS->createEntityFromLibrary("lib/libswarm.so");
    _ECS->createEntityFromLibrary("lib/libship.so");
    _ECS->createEntityFromLibrary("lib/libship.so");
    _ECS->createEntityFromLibrary("lib/libship.so");
    _ECS->createEntityFromLibrary("lib/libship.so");
}

void Scenes::Level2Scene::waveFour()
{
    // Spawning swarms
    _ECS->createEntityFromLibrary("lib/libswarm.so");
    _ECS->createEntityFromLibrary("lib/libswarm.so");
    _ECS->createEntityFromLibrary("lib/libfleet.so");
    _ECS->createEntityFromLibrary("lib/libship.so");
    _ECS->createEntityFromLibrary("lib/libship.so");
}