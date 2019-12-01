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
#include "menu.hpp"
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
        const sf::RenderWindow &window() const;

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

        /// \brief parse an udp packet
        /// \param packet : a pointer to the packet
        void parsePackets(void *packet);

        /// \brief return trackEvent
        /// \return the number containing a true/false for each byte
        std::size_t trackEvent() const;

        /// \brief detect events and threat them
        void processEvents();

        /// \brief display all entities on the window
        void display();

        /// \brief get the menu
        /// \return a reference to the menu
        Menu &menu();

        /// \brief add a key received from server to usable key on client
        /// \param comment : hint about what the key is used for
        void addKey(const std::string &);

    private:
        /// \brief get an entity from a packet
        /// \param packetHeader : the packet
        /// \return a pointer to a new entity
        Network::Entity *getEntityParams(Network::headerUdp *packetHeader);

        void generateBitmaskList();

        /*! window attribute */
        sf::RenderWindow _window;
        /*! view attribute */
        sf::View _view;
        /*! events attribute */
        sf::Event _events;
        /*! entities stocked attribute */
        std::map<std::size_t, std::shared_ptr<Client::Entity>> _entities;
        /*! entities stocked attribute */
        std::unordered_map<std::size_t, std::pair<std::string, sf::Texture>> _textures;
        /*! List of event with a small description */
        std::vector< std::pair<sf::Keyboard::Key, std::string> > _evtList;
        /*! Number used to store pressed buttons or not (bitwise operations) */
        std::size_t _trackEvent;
        /*! List of bitmask to set a specific bit to one or zero on _trackEvent */
        std::array<std::size_t, sizeof(size_t) * 8> _bitmaskList;
        /*! Menu interface */
        Menu _menu;
    };
}