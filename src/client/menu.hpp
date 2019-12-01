/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** GraphicalModule class declaration
*/

/// \file GraphicalModule.hpp
/// \author Lucas T.
/// \brief GraphicalModule class declaration

#pragma once

#include <memory>
#include <cstring>
#include <functional>
#include <SFML/Graphics.hpp>

#include "Exception.hpp"

namespace Client
{
    /// \class Menu
    /// \brief Create the menu
    class Menu {
    public:
        /// \brief Constructor
        /// \param window : window of the graphical client
        /// \param view : view of the graphical client
        Menu(sf::RenderWindow &window, sf::View &view);

        /// \brief detect events and threat them
        void processEvents();

        /// \brief display all sprites on the window
        void display();

        /// \brief generic menu of the client
        bool run();

        /// \brief create a sprite and texture that will be stored in the menu vector
        /// \param rect : rect of the texture
        /// \param pos : position of the sprite in the window
        /// \param callback : function callback when the sprite as been hit
        void createMenuElement(sf::IntRect &rect, sf::Vector2f &pos, std::function<void(Menu &)> &callback);

        /// \brief analyse the input form the player
        void analyseEvents();
    private:

        void callbackStart();
        void callbackOptions();
        void callbackQuit();

        /*! window attribute */
        sf::RenderWindow &_window;
        /*! window attribute */
        sf::View &_view;
        /*! events attribute */
        sf::Event _events;
        /*! a vector of sprites and their callbacks for the menu */
        std::vector<std::pair<std::function<void(Menu &)>, sf::Sprite>> _sprites;
        /*! the texture of the buttons */
        sf::Texture _texture;
        /*! check if the player clicked the start button */
        bool _start;
    };
}