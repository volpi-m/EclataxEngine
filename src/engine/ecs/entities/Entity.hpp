/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Entity class declaration
*/

/// \file Entity.hpp
/// \author Lucas T.
/// \brief Header file for the Entity class

#pragma once

#include <unordered_map>
#include <iostream>
#include <memory>
#include <vector>

#include "IComponent.hpp"

constexpr auto const default_tag = "";

/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {

    /// \class Entity
    /// \brief Entity class, create an entity in the game world that can old any components
    class Entity {
        public:
            /// \brief constructor
            /// Initialize Entity class
            /// \param tag (std::string) of the entity, default is empty
            Entity(const std::string &tag = default_tag);

            /// \brief constructor
            /// Initialize Entity class
            /// \param tag (raw char pointer) of the entity, default is empty
            Entity(const char *tag = default_tag);

            /// \brief copy constructor
            /// Initialize Entity class from another object
            /// \param entity : then entity to clone
            Entity(const Entity &entity);

            /// \brief destructor
            /// Destroy the Entity class
            ~Entity() = default;

            /// \brief Updates the Entity content
            void update();

            /// \param child : the Entity object that will be the current instance's child
            /// \brief Attach an entity to another
            void addChild(std::shared_ptr<Entity> &child);

            /// \param flag : the flag of the component
            /// \param component : the component to attach
            /// \brief Attach an entity to another
            void addComponent(flagType flag, std::shared_ptr<IComponent> &component);

            /// \param flag : the flag that we want to look for
            /// \return a shared pointer of a component
            /// \brief get a component from an the current instance
            std::shared_ptr<IComponent> component(flagType flag);

            /// \return a string containing the current instance's tag
            /// \brief get the tag of the current instance
            std::string tag() const;

            /// \param tag : string containing the new tag
            /// \brief set the tag of the current instance
            void setTag(const std::string &tag);

            /// \return the number of children of the entity
            /// \brief get the number of children of the entity
            std::size_t childrenSize() const;

            /// \return the vector of children
            /// \brief get all children of the entity
            const std::vector<std::shared_ptr<Entity>> &children() const;

            /// \param flag : the flag that we want to look for
            /// \return a boolean, true if the component is attached, false otherwise
            /// \brief Check if the component specified is attached to the entity
            bool hasComponent(flagType flag) const;

            /// \return a boolean, true if the entity is visible, false otherwise
            /// \brief Check if the entity is visible
            bool isVisible() const;

            /// \param state : visible state of the entity 
            /// \brief set the visible state of the entity
            void setVisible(bool state);

            /// \brief mark the current entity as deleted and all of its children
            void deleteEntity();

            /// \return a boolean, true if the entity is deleted, false otherwise
            /// \brief Check if the entity is deleted
            bool deleted() const;

        private:

            /*! tag of the entity */
            std::string _tag;
            /*! list of components attached to the entity */
            std::unordered_map<flagType, std::shared_ptr<IComponent>> _components;
            /*! children of the entity */
            std::vector<std::shared_ptr<Entity>> _children;
            /*! has the entity been deleted */
            bool _deleted;
            /*! is the entity visible */
            bool _visible;
    };
}