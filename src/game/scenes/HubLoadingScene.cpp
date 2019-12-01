/*
** EPITECH PROJECT, 2019
** rType
** File description:
** HubLoading scene
*/

#include "HubLoadingScene.hpp"

Scenes::HubLoadingScene::HubLoadingScene(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS) : AScene(name, ECS)
{
    initComponents();
}

Scenes::HubLoadingScene::HubLoadingScene(const char *name, std::shared_ptr<Module::EntityComponentSystem> &ECS) : AScene(name, ECS)
{
    initComponents();
}

Scenes::HubLoadingScene::~HubLoadingScene()
{
}

Scenes::IScene *Scenes::HubLoadingScene::run()
{
    return nullptr;
}

void Scenes::HubLoadingScene::setVisible(bool state)
{

}

void Scenes::HubLoadingScene::remove()
{

}

void Scenes::HubLoadingScene::initComponents()
{
    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform(0, 0, 0));
    std::shared_ptr<ECS::IComponent> sprite(new ECS::Component::Sprite("ressources/.png", Game::Rect(0, 0, 622, 368)));
    std::shared_ptr<ECS::IComponent> text(new ECS::Component::Text("Press Space when you are ready !"));
    std::shared_ptr<ECS::System::TextSystem> system(new ECS::System::TextSystem());

    unsigned long long bgId = _ECS->createEntity("Background");
    unsigned long long textId = _ECS->createEntity("text");
    _ECS->addComponentToEntity(bgId, ECS::Component::Flags::transform, transform);
    _ECS->addComponentToEntity(bgId, ECS::Component::Flags::sprite, sprite);
    _ECS->addComponentToEntity(textId, ECS::Component::Flags::text, text);
    pushEntityStack(_ECS->entity(bgId), bgId);
    pushEntityStack(_ECS->entity(textId), textId);
}

void Scenes::HubLoadingScene::handleEvent(std::queue<std::pair<int, size_t>> &events)
{
    while(!events.empty()) {
        if (events.front().second & Scenes::Event::SPACE) {
            displayPlayer(static_cast<unsigned int>(events.front().first));
        }
    }
}

void Scenes::HubLoadingScene::displayPlayer(unsigned int playerNb) {
    if (playerNb <= _playerStat.size()) {
        if (_playerStat[playerNb].state) {
            _playerStat[playerNb].state = false;
            if (_ECS->hasComponent(_playerStat[playerNb].text, ECS::Component::Flags::text))
                static_cast<ECS::System::TextSystem *>(_ECS->system(ECS::Component::Flags::text).get())->setText(_ECS->entity(_playerStat[playerNb].text), "Player is not ready");
        } else {
            if (_ECS->hasComponent(_playerStat[playerNb].text, ECS::Component::Flags::text))
                static_cast<ECS::System::TextSystem *>(_ECS->system(ECS::Component::Flags::text).get())->setText(_ECS->entity(_playerStat[playerNb].text), "Ready to fight !");
        }
        _playerStat[playerNb].state = !_playerStat[playerNb].state;
    } else {
        _ECS->createEntityFromLibrary(SHIP_PATH);
        std::shared_ptr<ECS::IComponent> text(new ECS::Component::Text("The player is not ready"));
        unsigned long long newText = _ECS->createEntity("playerText");
        _playerStat.emplace_back(false, newText);
    }
}
