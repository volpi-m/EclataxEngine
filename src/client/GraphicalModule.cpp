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

Client::GraphicalModule::GraphicalModule() : _window(sf::RenderWindow(sf::VideoMode(1920, 1080), "SFML works!")), _closed(false) {}

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

void Client::GraphicalModule::processEvents()
{
    while (_window.pollEvent(_events)) {

        // The window has been closed
        if (_events.type == sf::Event::Closed) {
            _window.close();
            _closed = true;
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