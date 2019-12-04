/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** MovementSystem class declaration
*/

/// \file TextSystem.hpp
/// \author Lucas T.
/// \brief TextSystem class declaration

#pragma once

#include <vector>

#include "ISystem.hpp"
#include "Entity.hpp"
#include "Logger.hpp"
#include "TextComponent.hpp"

/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {
    /// \namespace System
    /// \brief Used for the all System
    namespace System {

        /// \class TextSystem
        /// \brief A system that will update the Text component
        class TextSystem : public ISystem {
            public:
                /// \param entities : entities that needs to be updated
                /// \brief update all entities with the current system
                void update(std::unordered_map<unsigned long long, std::shared_ptr<Entity>> &entities) override;

                /// \return the text of the current entity
                /// \param entity : the target entityText
                /// \brief get the text of the tageted entity
                const std::string &text(std::shared_ptr<Entity> &entity) const;
                /// \return the text of the current entity
                /// \param entity : the target entityText
                /// \brief get the text of the tageted entity
                const std::string &font(std::shared_ptr<Entity> &entity) const;
                /// \param entity : the target entityText
                /// \param newText : new text
                /// \brief set a new text to the component
                void setText(std::shared_ptr<Entity> &entity, const std::string &newText);
                /// \param entity : the target entityText
                /// \param newFont : path to the new font
                /// \brief get the text of the tageted entity
                void setFont(std::shared_ptr<Entity> &entity, const std::string &newFont);
        };
    }
}