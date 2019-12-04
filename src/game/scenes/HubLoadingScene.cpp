/*
** EPITECH PROJECT, 2019
** rType
** File description:
** HubLoading scene
*/

#include "HubLoadingScene.hpp"

Scenes::HubLoadingScene::HubLoadingScene(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS, int playersNb) : AScene(name, ECS, playersNb)
{
    initComponents();
}

Scenes::HubLoadingScene::HubLoadingScene(const char *name, std::shared_ptr<Module::EntityComponentSystem> &ECS, int playersNb) : AScene(name, ECS, playersNb)
{
    initComponents();
}

Scenes::HubLoadingScene::~HubLoadingScene()
{
}

Scenes::IScene *Scenes::HubLoadingScene::run()
{
    auto ids = _ECS->ids();
    _ECS->update();
    for (unsigned long long id = 0; id < ids.size() && _ECS->hasEntity(ids[id]); ++id)
        pushEntityStack(_ECS->entity(ids[id]), ids[id]);
    _ECS->clearEntities();
    return nullptr;
}

void Scenes::HubLoadingScene::setVisible([[maybe_unused]]bool state)
{

}

void Scenes::HubLoadingScene::remove()
{
    auto ids = _ECS->ids();
    for (auto id : ids)
        _ECS->entity(id)->deleteEntity();
    for (unsigned long long id = 0; id < ids.size() && _ECS->hasEntity(ids[id]); ++id)
        pushEntityStack(_ECS->entity(ids[id]), ids[id]);
    _ECS->clear();
}

void Scenes::HubLoadingScene::initComponents()
{
    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform(0, 0, 0));
    std::shared_ptr<ECS::IComponent> sprite(new ECS::Component::Sprite("ressources/level_1.jpg", Game::Rect(0, 0, 1920, 1080)));

    std::shared_ptr<ECS::ISystem>render(new ECS::System::RenderSystem());
    std::shared_ptr<ECS::ISystem>mov(new ECS::System::MovementSystem());
    _ECS->addSystem(ECS::System::Flags::RenderSystem, render);
    _ECS->addSystem(ECS::System::Flags::Movement, mov);

    unsigned long long bgId = _ECS->createEntity("Background");
    _ECS->addComponentToEntity(bgId, ECS::Component::Flags::transform, transform);
    _ECS->addComponentToEntity(bgId, ECS::Component::Flags::sprite, sprite);
    pushEntityStack(_ECS->entity(bgId), bgId);
    createCategory(0);
}

void Scenes::HubLoadingScene::handleEvent(std::queue<std::pair<int, size_t>> events)
{
    while (!events.empty()) {
        if ((events.front().second & Scenes::Event::SPACE) == Scenes::Event::SPACE) {
            displayPlayer(events.front().first - 1);
        }
        events.pop();
    }
}

void Scenes::HubLoadingScene::displayPlayer(int playerNb)
{
    if (static_cast<unsigned int>(playerNb + 1) <= _playerStat.size()) {
        if (!_playerStat[playerNb].state) {
            if (_ECS->hasComponent(_playerStat[playerNb].ico, ECS::Component::Flags::sprite))
                static_cast<ECS::System::RenderSystem *>(_ECS->system(ECS::System::Flags::RenderSystem).get())->setTexture(_ECS->entity(_playerStat[playerNb].ico), CHECK_PATH);
            _playerStat[playerNb].state = !_playerStat[playerNb].state;
        }
    } else {
        createCategory(playerNb);
    }
}

void Scenes::HubLoadingScene::createCategory(int pos)
{
    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform((1920 / 2 - 100), 150 + (pos * 200), 0));
    std::shared_ptr<ECS::IComponent> sprite(new ECS::Component::Sprite(CROSS_PATH, Game::Rect(0, 0, 200, 200)));
    unsigned long long ico = _ECS->createEntity("player ico");
    unsigned long long ship = _ECS->createEntityFromLibrary(PLAYER_SHIP_PATH);
    static_cast<ECS::System::MovementSystem *>(_ECS->system(ECS::System::Flags::Movement).get())->setTransform(_ECS->entity(ship), 1920 / 2, 250 + (pos * 250), 0);
    _ECS->addComponentToEntity(ico, ECS::Component::Flags::sprite, sprite);
    _ECS->addComponentToEntity(ico, ECS::Component::Flags::transform, transform);
    _playerStat.emplace_back(false, ico);
}