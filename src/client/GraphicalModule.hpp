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
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "EntityClient.hpp"
#include "Rfc.hpp"

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
        void createEntity(std::size_t id);

        /// \brief create a new entity and store it
        /// \param id : the id of the new entity
        /// \param txtId : the id to the texture
        void createEntity(std::size_t id, std::size_t txtId);

        /// \brief create multiple new entities and store them
        /// \param id : ids of the new entities
        void createMultipleEntities(std::vector<std::size_t> &ids);

        /// \brief adds a texture to the client
        /// \param filepath : filepath to the teture
        /// \return an index to the texture
        std::size_t addTexture(const std::string &filepath);

        /// \brief run the graphical client
        /// \return a bool that is true is the client is closed, false otherwise
        bool run();

        /// \brief parse an udp packet
        /// \param packet : a pointer to the packet
        void parsePackets(void *packet);

    private:
        /// \brief detect events and threat them
        void processEvents();

        /// \brief get an entity from a packet
        /// \param packetHeader : the packet
        /// \return a pointer to a new entity
        Network::Entity *getEntityParams(Network::headerUdp *packetHeader);

        /// \brief display all entiites on the window
        void display();

        /*! window attribute */
        sf::RenderWindow _window;
        /*! events attribute */
        sf::Event _events;
        /*! entities stocked attribute */
        std::unordered_map<std::size_t, std::shared_ptr<Client::Entity>> _entities;
        /*! entities stocked attribute */
        std::unordered_map<std::size_t, std::pair<std::string, sf::Texture>> _textures;
        /*! closed window attribute */
        bool _closed;
    };
}