/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component TEMPLATE
*/

/// \file GraphicalModule.cpp
/// \author Someone
/// \brief GraphicalModule methods

#include "GraphicalModule.hpp"

Client::GraphicalModule::GraphicalModule()
    : _window(sf::RenderWindow(sf::VideoMode::getDesktopMode(), "EclataxEngine Client")),
    _trackEvent(0), _menu(Client::Menu(_window, _view))
{
    _window.setFramerateLimit(60);
    sf::Texture artefact;
    auto size = sf::VideoMode::getDesktopMode();

    // Creating an artefact texture
    artefact.create(50, 50);
    _textures.emplace(0, std::make_pair("artefact", artefact));

    generateBitmaskList();

    _view.setCenter((float)size.width / 2, (float)size.height / 2);
    _view.setSize((sf::Vector2f) {(float)size.width, (float)size.height});
    _window.setView(_view);

    _evtList.push_back({sf::Keyboard::Key::Z, "Move Up"});
    _evtList.push_back({sf::Keyboard::Key::S, "Move Down"});
    _evtList.push_back({sf::Keyboard::Key::Q, "Move Left"});
    _evtList.push_back({sf::Keyboard::Key::D, "Move Right"});
    _evtList.push_back({sf::Keyboard::Key::Enter, "Enter"});
    _evtList.push_back({sf::Keyboard::Key::Space, "Space"});
    _evtList.push_back({sf::Keyboard::Key::Escape, "Escape"});
}

const sf::RenderWindow &Client::GraphicalModule::window() const
{
    return _window;
}

void Client::GraphicalModule::createEntity(std::size_t id)
{
    if (_entities.find(id) != _entities.end())
        return;

    std::shared_ptr<Client::Entity> entity(new Client::Entity(_textures[0].second));

    _entities.emplace(id, entity);
}

void Client::GraphicalModule::createEntity(std::size_t id, std::size_t txtId)
{
    if (_entities.find(id) != _entities.end()) {
        if (_entities[id]->textureIdx() != txtId)
            _entities[id]->setTextureIdx(txtId, _textures[txtId].second);
        return;
    }

    std::shared_ptr<Client::Entity> entity(new Client::Entity(_textures[txtId].second, txtId));

    _entities.emplace(id, entity);
}

std::size_t Client::GraphicalModule::addTexture(const std::string &filepath)
{
    // Checking if the texture already exists
    for (auto &it : _textures)
        if (it.second.first == filepath)
            return it.first;

    // If not, adding it to our unordered map
    sf::Texture newTexture;

    // Checking if the texture can be loaded
    if (!newTexture.loadFromFile(filepath))
        return 0;
    _textures.emplace(_textures.size() + 1, std::make_pair(filepath, newTexture));
    return _textures.size();
}

void Client::GraphicalModule::parsePackets(void *packet)
{
    Network::headerUdp *packetHeader = static_cast<Network::headerUdp *>(packet);
    Network::Entity *entity = nullptr;

    // The server sent data about an entity
    if (packetHeader->code == Network::SERVER_TICK)
        entity = getEntityParams(packetHeader);
    if (entity) {
        
        if (entity->deleted) {
            _entities.erase(entity->id);
            return;
        }
        // Creating the entity and eventualy the texture
        std::size_t id = addTexture((char *)entity->texture);
        createEntity(entity->id, id);

        // Setting entity position and rectangle
        _entities[entity->id]->setPosition(entity->x, entity->y, entity->z);
        _entities[entity->id]->setTextureRect(entity->top, entity->left, entity->width, entity->height);
    }
}

Network::Entity *Client::GraphicalModule::getEntityParams(Network::headerUdp *packetHeader)
{
    // getting the length of the path of the texture
    unsigned int len = Network::UDP_BUF_SIZE - (sizeof(unsigned long long) + sizeof(char) + sizeof(float) * 7);
    Network::Entity *packetEntity = new Network::Entity;

    // Copying all packet data into the structure
    std::memcpy(&(packetEntity->id), (unsigned long long *)packetHeader->data, sizeof(unsigned long long));
    std::memcpy(&(packetEntity->x), (float *)(packetHeader->data + sizeof(unsigned long long)), sizeof(float));
    std::memcpy(&(packetEntity->y), (float *)(packetHeader->data + sizeof(unsigned long long) + sizeof(float)), sizeof(float));
    std::memcpy(&(packetEntity->z), (float *)(packetHeader->data + sizeof(unsigned long long) + sizeof(float) * 2), sizeof(float));
    std::memcpy(&(packetEntity->top), (float *)(packetHeader->data + sizeof(unsigned long long) + sizeof(float) * 3), sizeof(float));
    std::memcpy(&(packetEntity->left), (float *)(packetHeader->data + sizeof(unsigned long long) + sizeof(float) * 4), sizeof(float));
    std::memcpy(&(packetEntity->width), (float *)(packetHeader->data + sizeof(unsigned long long) + sizeof(float) * 5), sizeof(float));
    std::memcpy(&(packetEntity->height), (float *)(packetHeader->data + sizeof(unsigned long long) + sizeof(float) * 6), sizeof(float));
    std::memcpy(&(packetEntity->deleted), (char *)(packetHeader->data + sizeof(unsigned long long) + sizeof(float) * 7), sizeof(char));
    std::memcpy(packetEntity->texture, packetHeader->data + sizeof(unsigned long long) + sizeof(char) + sizeof(float) * 7, len);
 
    return packetEntity;
}

void Client::GraphicalModule::generateBitmaskList()
{
    for (std::size_t i = 0, n = 1; i < sizeof(size_t) * 8; i++, n = n << 1)
        _bitmaskList[i] = n;
}

std::size_t Client::GraphicalModule::trackEvent() const
{
    return _trackEvent;
}

void Client::GraphicalModule::processEvents()
{
    while (_window.pollEvent(_events)) {

        // The window has been closed
        if (_events.type == sf::Event::Closed) {
            _window.close();
        }
        for (uint i = 0; i < _evtList.size(); i++)
            if (sf::Keyboard::isKeyPressed(_evtList[i].first)) {
                _trackEvent |= _bitmaskList[i];
            } else if (_events.type == sf::Event::KeyReleased && _events.key.code == _evtList[i].first) {
                _trackEvent ^= _bitmaskList[i];
            }
    }
}

void Client::GraphicalModule::display()
{
    // Clear the screen
    _window.clear();

    // Draw all entities
    for (auto &it : _entities)
        _window.draw(it.second->sprite());

    // Display all drawings
    _window.display();
}

Client::Menu &Client::GraphicalModule::menu()
{
    return _menu;
}

void Client::GraphicalModule::addKey(const std::string &comment)
{
    _evtList.push_back({sf::Keyboard::Key::Unknown, comment});
}
