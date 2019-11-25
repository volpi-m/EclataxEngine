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
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "EntityClient.hpp"

namespace Client
{
    /// \class GraphicalModule
    /// \brief Create Entity and draw them on screen
    class GraphicalModule
    {
    public:
        /// \brief Constructor
        GraphicalModule();

        /// \brief get the render window
        /// \return a reference to the render window
        sf::RenderWindow &window();

        /// \brief create a new entity and store it
        /// \param id : the id of the new entity
        /// \param rect : scale of the new entity
        void createEntity(unsigned long long id, sf::IntRect &rect);

        /// \brief create a new entity and store it
        /// \param id : the id of the new entity
        /// \param filepath : the filepath to the texture
        /// \param rect : scale of the new entity
        void createEntity(unsigned long long id, const std::string &filepath, sf::IntRect &rect);

        /// \brief create multiple new entities and store them
        /// \param id : ids of the new entities
        void createMultipleEntities(std::vector<unsigned long long> &ids);

        /// \brief run the graphical client
        /// \return a bool that is true is the client is closed, false otherwise
        bool run();

    private:
        /// \brief detect events and threat them
        void processEvents();

        /// \brief display all entiites on the window
        void display();

        /*! window attribute */
        sf::RenderWindow _window;
        /*! events attribute */
        sf::Event _events;
        /*! entities stocked attribute */
        std::unordered_map<unsigned long long, Entity> _entities;
        /*! closed window attribute */
        bool _closed;
    };
}