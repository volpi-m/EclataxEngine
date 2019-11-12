/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Game Engine methods
*/

/// \file ECS.hpp
/// \author Lucas T.
/// \brief ECS class declaration

#pragma once

#include <string>
#include <optional>

#include "IComponent.hpp"
#include "IModule.hpp"
#include "ISystem.hpp"
#include "Entity.hpp"

/// \namespace Module
/// \brief Used for all GameEngine modules
namespace Module {

    /// \class EntityComponentSystem
    /// \brief EntityComponentSystem class module from the game engine
    class EntityComponentSystem : public IModule {
    public:
        // IMPLEMENTED METHODS

        /// \brief constructor
        EntityComponentSystem();

        /// \brief destructor
        ~EntityComponentSystem() = default;

        /// \param system : The system to add to the ECS's system list
        /// \brief add a system to the ECS's system list
        void addSystem(std::unique_ptr<ECS::ISystem> &system);

        /// \param tag : the new name of the current scene
        /// \param ECS : ECS instance to pass to the scene
        /// \brief scene constructor
        unsigned long long createEntity(const std::string &tag = "");

        /// \param tag : the new name of the current scene
        /// \param ECS : ECS instance to pass to the scene
        /// \brief scene constructor
        unsigned long long createEntity(const char *tag = "");

        /// \param id : the id of the entity
        /// \param flag : the component flag
        /// \param component : the component to attach to the entity 
        /// \brief add a component to an existing entity
        void addComponentToEntity(unsigned long long id, ECS::flagType flag, std::shared_ptr<ECS::IComponent> &component);

        /// \param id : the id of the entity
        /// \param state : the visible state
        /// \brief set the visible set of an entity
        void setEntityVisibleState(unsigned long long id, bool state);

        /// \param id : the id of the entity
        /// \return true of the entity is visible, false otherwise
        /// \brief check if the entity is visibke
        bool isEntityVisible(unsigned long long id);

        /// \param id : the id of the entity
        /// \return true of the entity exists, false otherwise
        /// \brief check if the entity exists
        bool hasEntity(unsigned long long id) const;

        /// \param id : the id of the entity
        /// \param type : type of the component
        /// \return true of the entity has the component, false otherwise
        /// \brief check if the entity has the component
        bool hasComponent(unsigned long long id, ECS::flagType type);

        /// \param id : the id of the entity
        /// \return the tag of the entity
        /// \brief get the tag of an entity
        std::string tag(unsigned long long id);

        std::size_t systems() const;

        /// \return true if the ECS instance is initialised, false otherwise
        /// \brief check if the ECS instance is initialised
        bool isInitialised() override;

        // NOT YET IMPLEMENTED
        void update();
        unsigned long long createChildEntity(unsigned long long id, const std::string &tag = "");
        void setEntityPosition(unsigned long long id, unsigned int x, unsigned int y);
        void setEntitySpeed(unsigned long long id, unsigned int damage);
        void setEntityDamage(unsigned long long id, unsigned int damage);
        std::optional<unsigned long long> checkCollision(unsigned long long id);
        //ECS::Entity getEntity(unsigned long long id);
        void entityDebugCollisionBox(unsigned long long id, bool show);
    private:
        /*! Module initialisation method */
        void init() override;
        /*! Module initialisation method */
        unsigned long long _newId;
        /*! has the ECS module been initialised */
        bool _initialised;
        /*! System vector */
        std::vector<std::unique_ptr<ECS::ISystem>> _systems;
        /*! Entities unordered map (id and instance) */
        std::unordered_map<unsigned long long, std::shared_ptr<ECS::Entity>> _entities;
    };
}
