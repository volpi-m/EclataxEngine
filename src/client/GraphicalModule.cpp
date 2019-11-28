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
    : _window(sf::RenderWindow(sf::VideoMode(1920, 1080), "SFML works!")), _closed(false),
    _trackEvent(0), _bitmaskList({1, 2, 4, 8, 16, 32, 64, 128})
{
    _evtList.push_back({sf::Keyboard::Key::Z, "Move Up"});
    _evtList.push_back({sf::Keyboard::Key::S, "Move Down"});
    _evtList.push_back({sf::Keyboard::Key::Q, "Move Left"});
    _evtList.push_back({sf::Keyboard::Key::D, "Move Right"});
    _evtList.push_back({sf::Keyboard::Key::Num1, "1"});
    _evtList.push_back({sf::Keyboard::Key::Num2, "2"});
    _evtList.push_back({sf::Keyboard::Key::Num3, "3"});
    _evtList.push_back({sf::Keyboard::Key::Num5, "5"});
}

sf::RenderWindow &Client::GraphicalModule::window()
{
    return _window;
}

void Client::GraphicalModule::createEntity(unsigned long long id, sf::IntRect &rect)
{
    _entities.emplace(id, Entity(rect));
}

void Client::GraphicalModule::createEntity(unsigned long long id, const std::string &filepath, sf::IntRect &rect)
{
    _entities.emplace(id, Entity(filepath, rect));
}

bool Client::GraphicalModule::run()
{
    if (_window.isOpen()) {

        // Process events and display them
        processEvents();
        display();
    }
    return _closed;
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
            _closed = true;
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
        _window.draw(it.second.sprite());
    
    // Display all drawings
    _window.display();
}