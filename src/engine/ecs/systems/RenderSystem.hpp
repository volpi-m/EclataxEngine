/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** RenderSystem class declaration
*/

/// \file RenderSystem.hpp
/// \author Lucas T.
/// \brief RenderSystem class declaration

#pragma once

#include "ISystem.hpp"
#include "Entity.hpp"
#include "SpriteComponent.hpp"

/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {
    /// \namespace System
    /// \brief Used for the all System
    namespace System {

        /// \class RenderSystem
        /// \brief A system that will update the Sprite component
        class RenderSystem : public ISystem {
            public:
                /// \param entities : entities that needs to be updated
                /// \brief update all entities with the current system
                void update(std::unordered_map<unsigned long long, std::shared_ptr<Entity>> &entities) override;

                /// \brief get the texture of the current sprite
                /// \return the name of the file containing the texture
                std::string texture(std::shared_ptr<ECS::Entity> &entity) const;
                
                /// \brief adds a texture to the sprite component
                /// \param entity : texture file to add to the sprite
                /// \param texture : texture file to add to the sprite
                void setTexture(std::shared_ptr<ECS::Entity> &entity, const std::string &texture);

                /// \brief the sprite is loaded by the client. (the client tries to load the sprite until the atttribute is set to true)
                /// \param entity : texture file to add to the sprite
                void setLoaded(std::shared_ptr<ECS::Entity> &entity);

                /// \brief the sprite is loaded by the client. (the client tries to load the sprite until the atttribute is set to true)
                /// \param entity : texture file to add to the sprite
                /// \return as the sprite of the entity as been correctly loaded
                bool loaded(const std::shared_ptr<ECS::Entity> &entity) const;
        };
    }
}