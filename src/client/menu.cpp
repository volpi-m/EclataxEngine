/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component TEMPLATE
*/

/// \file GraphicalModule.cpp
/// \author Someone
/// \brief GraphicalModule methods

#include "menu.hpp"

Client::Menu::Menu(sf::RenderWindow &window, sf::View &view) : _window(window), _view(view), _start(false)
{
    if (!_texture.loadFromFile("ressources/menu.png"))
        throw Debug::Exception("Couldn't load textures for the menu", "Client::Menu::Menu");

    // Options of the sprites.
    sf::IntRect rect(0, 0, 200, 100);
    auto windowSize = _view.getSize();
    sf::Vector2f pos(windowSize.x, windowSize.y / 3);

    // Creating callbacks.
    std::array<std::function<void(Menu &)>, 3> callbacks = {&Menu::callbackStart, &Menu::callbackOptions, &Menu::callbackQuit};

    // Creating sprites and assigning the texture.
    for (unsigned int i = 0; i < callbacks.size(); ++i)
    {
        createMenuElement(rect, pos, callbacks[i]);
        rect.left += 200;
        pos.y += windowSize.y / 3;
    }
}

void Client::Menu::processEvents()
{
    while (_window.pollEvent(_events))
    {

        // The window has been closed.
        if (_events.type == sf::Event::Closed)
            _window.close();
    }
}

void Client::Menu::display()
{
    // Clear the screen.
    _window.clear();

    // Draw all entities.
    for (auto &it : _sprites)
        _window.draw(it.second);
    
    // Display all drawings.
    _window.display();
}

bool Client::Menu::run()
{
    _start = false;
    while (_window.isOpen() && !_start)
    {
        while (_window.pollEvent(_events))
        {
            // The window has been closed.
            if (_events.type == sf::Event::Closed ||
            (_events.type == sf::Event::KeyReleased && _events.key.code == sf::Keyboard::Escape))
                _window.close();
            analyseEvents();
        }
        display();
    }
    return _start;
}

void Client::Menu::createMenuElement(sf::IntRect &rect, sf::Vector2f &pos, std::function<void(Menu &)> &callback)
{
    _sprites.emplace(_sprites.end(), std::make_pair(callback, sf::Sprite(_texture, rect)));

    _sprites.back().second.setOrigin((sf::Vector2f) {(float)rect.width / 2, (float)rect.height / 2});
    _sprites.back().second.setPosition((sf::Vector2f) {pos.x, pos.y - rect.height});
}

void Client::Menu::analyseEvents()
{
    auto translated_pos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));

    for (auto &it : _sprites)
    {
        if (it.second.getGlobalBounds().contains(translated_pos))
            it.second.setColor((sf::Color) {255, 255, 255, 255});
        else
            it.second.setColor((sf::Color) {255, 255, 255, 150});
    }
    if (_events.type == sf::Event::MouseButtonPressed)
        for (auto &it : _sprites)
            if (it.second.getGlobalBounds().contains(translated_pos))
                it.first(*this);
}

void Client::Menu::callbackStart()
{
    _start = true;

    // sf::Vector2u wSize = _window.getSize();
    // sf::RectangleShape selector((sf::Vector2f) {(float)wSize.x, (float)wSize.y});

    // selector.setOrigin((sf::Vector2f) {(float)wSize.x / 2, (float)wSize.y / 2});
    // selector.setPosition((sf::Vector2f) {(float)wSize.x / 2, (float)wSize.y / 2});
    // selector.setFillColor(sf::Color(255, 255, 0));
    // selector.setOutlineColor(sf::Color(255, 255, 255));
    // selector.setOutlineThickness(20);

    // // Setting parameters of the scroll view.
    // _scroll.setSize((sf::Vector2f) {(float)wSize.x / 1.5f, (float)wSize.y / 1.5f});
    // _scroll.setCenter((sf::Vector2f) {(float)wSize.x / 3, (float)wSize.y / 3});
    // _scroll.setViewport(sf::FloatRect(0, 0, 1, 1));

    // _window.setView(_scroll);

    // while (_window.isOpen())
    // {
    //     while (_window.pollEvent(_events))
    //     {
    //         // The window has been closed.
    //         if (_events.type == sf::Event::Closed)
    //             _window.close();
    //         else if (_events.type == sf::Event::KeyReleased && _events.key.code == sf::Keyboard::Escape)
    //            return;
    //     }

    //     // displaying objects
    //     _window.clear(sf::Color::Black);
    //     _window.draw(selector);
    //     _window.display();
    // }
}

void Client::Menu::callbackOptions()
{
    std::cout << "OPTIONS" << std::endl;
}

void Client::Menu::callbackQuit()
{
    _window.close();
}
