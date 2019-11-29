/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** EntityFactory class declaration
*/

/// \file EntityFactory.hpp
/// \author Lucas T.
/// \brief Header file for the EntityFactory class

#pragma once

#include "Entity.hpp"
#include "AccelerationComponent.hpp"
#include "AudioComponent.hpp"
#include "CollisionBox2DComponent.hpp"
#include "DamageComponent.hpp"
#include "HealthComponent.hpp"
#include "LifeComponent.hpp"
#include "ParticulesComponent.hpp"
#include "ScriptComponent.hpp"
#include "SpawnerComponent.hpp"
#include "SpeedComponent.hpp"
#include "SpriteComponent.hpp"
#include "TextComponent.hpp"
#include "TransformComponent.hpp"

/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {

    /// \class EntityFactory
    /// \brief EntityFactory class, create an entity from a blueprint
    class EntityFactory {
        public:
            /// \brief constructor
            /// Initialize Entity class
            EntityFactory() = default;

            /// \brief destructor
            /// Destroy the Entity class
            ~EntityFactory() = default;

            /// \brief Check if the key is stored
            /// \param key : the name of the blueprint
            /// \return a boolean, true if the blueprint is stored, false otherwise
            bool hasEntity(const std::string &key);

            /// \brief register an entity
            /// \param key : the name of the blueprint
            /// \param entity : the entity to copy as a blueprint
            void registerEntity(const std::string &key, Entity &entity);

            /// \brief register an entity
            /// \param key : the name of the blueprint
            /// \param types : types of all components
            void registerEntity(const std::string &key, ECS::flagType types);

            /// \brief create an entity from a blueprint
            /// \param key : the name of the blueprint
            /// \return a new entity based on the blueprint
            std::shared_ptr<Entity> createEntity(const std::string &key);

            std::shared_ptr<Entity> createEntity(ECS::Entity &entity, ECS::flagType types);

        private:
            /*! list of entity blueprints */
            std::unordered_map<std::string, Entity> _blueprints;

            /*! an array of component flags */
            std::array<flagType, 13> _flags {
                Component::Flags::acceleration,
                Component::Flags::audio,
                Component::Flags::collisionBox2D,
                Component::Flags::damage,
                Component::Flags::health,
                Component::Flags::life,
                Component::Flags::particules,
                Component::Flags::script,
                Component::Flags::spawner,
                Component::Flags::speed,
                Component::Flags::sprite,
                Component::Flags::text,
                Component::Flags::transform
            };

            /*! the component factory */
            std::shared_ptr<IComponent> (* const _emptyComponentFactory[13])() {
                []()->std::shared_ptr<IComponent> { return std::shared_ptr<IComponent>(new Component::Acceleration); },
                []()->std::shared_ptr<IComponent> { return std::shared_ptr<IComponent>(new Component::Audio); },
                []()->std::shared_ptr<IComponent> { return std::shared_ptr<IComponent>(new Component::CollisionBox2D); },
                []()->std::shared_ptr<IComponent> { return std::shared_ptr<IComponent>(new Component::Damage); },
                []()->std::shared_ptr<IComponent> { return std::shared_ptr<IComponent>(new Component::Health); },
                []()->std::shared_ptr<IComponent> { return std::shared_ptr<IComponent>(new Component::Life); },
                []()->std::shared_ptr<IComponent> { return std::shared_ptr<IComponent>(new Component::Particules); },
                []()->std::shared_ptr<IComponent> { return std::shared_ptr<IComponent>(new Component::Script); },
                []()->std::shared_ptr<IComponent> { return std::shared_ptr<IComponent>(new Component::Spawner); },
                []()->std::shared_ptr<IComponent> { return std::shared_ptr<IComponent>(new Component::Speed); },
                []()->std::shared_ptr<IComponent> { return std::shared_ptr<IComponent>(new Component::Sprite); },
                []()->std::shared_ptr<IComponent> { return std::shared_ptr<IComponent>(new Component::Text); },
                []()->std::shared_ptr<IComponent> { return std::shared_ptr<IComponent>(new Component::Transform); },
            };

            std::shared_ptr<IComponent> (* const _copyComponentFactory[13])(const std::shared_ptr<IComponent> &component) {

                // Copy the Acceleration component
                [](const std::shared_ptr<IComponent> &component)->std::shared_ptr<IComponent>
                {
                    auto toCopy = static_cast<Component::Acceleration *>(component.get());
                    std::shared_ptr<IComponent> acceleration(new Component::Acceleration(toCopy->acceleration));

                    return acceleration;
                },

                // Copy the Audio component
                [](const std::shared_ptr<IComponent> &component)->std::shared_ptr<IComponent>
                {
                    auto toCopy = static_cast<Component::Audio *>(component.get());
                    std::shared_ptr<IComponent> audio(new Component::Audio(toCopy->file, toCopy->active));

                    return audio;
                },

                // Copy the CollisionBox2D component
                [](const std::shared_ptr<IComponent> &component)->std::shared_ptr<IComponent>
                {
                    auto toCopy = static_cast<Component::CollisionBox2D *>(component.get());
                    std::shared_ptr<IComponent> collisionBox2D(new Component::CollisionBox2D(toCopy->rectangle.top, toCopy->rectangle.left, toCopy->rectangle.width, toCopy->rectangle.height));

                    return collisionBox2D;
                },

                // Copy the Damage component
                [](const std::shared_ptr<IComponent> &component)->std::shared_ptr<IComponent>
                {
                    auto toCopy = static_cast<Component::Damage *>(component.get());
                    std::shared_ptr<IComponent> damage(new Component::Damage(toCopy->damage));

                    return damage;
                },

                // Copy the Health component
                [](const std::shared_ptr<IComponent> &component)->std::shared_ptr<IComponent>
                {
                    auto toCopy = static_cast<Component::Health *>(component.get());
                    std::shared_ptr<IComponent> health(new Component::Health(toCopy->health, toCopy->healthLimit));

                    return health;
                },

                // Copy the Life component
                [](const std::shared_ptr<IComponent> &component)->std::shared_ptr<IComponent>
                {
                    auto toCopy = static_cast<Component::Life *>(component.get());
                    std::shared_ptr<IComponent> life(new Component::Life(toCopy->lifes));

                    return life;
                },

                // Copy the Particules component
                [](const std::shared_ptr<IComponent> &component)->std::shared_ptr<IComponent>
                {
                    auto toCopy = static_cast<Component::Particules *>(component.get());
                    std::shared_ptr<IComponent> particules(new Component::Particules(toCopy->samples, toCopy->size, toCopy->speed));

                    return particules;
                },

                // Copy the Script component
                [](const std::shared_ptr<IComponent> &component)->std::shared_ptr<IComponent>
                {
                    auto toCopy = static_cast<Component::Script *>(component.get());
                    std::shared_ptr<IComponent> script(new Component::Script(toCopy->updateScript));

                    return script;
                },

                // Copy the Spawner component
                [](const std::shared_ptr<IComponent> &component)->std::shared_ptr<IComponent>
                {
                    auto toCopy = static_cast<Component::Spawner *>(component.get());
                    std::shared_ptr<IComponent> spawner(new Component::Spawner(toCopy->seconds, toCopy->createBlueprint));

                    return spawner;
                },

                // Copy the Speed component
                [](const std::shared_ptr<IComponent> &component)->std::shared_ptr<IComponent>
                {
                    auto toCopy = static_cast<Component::Speed *>(component.get());
                    std::shared_ptr<IComponent> sprite(new Component::Speed(toCopy->speed));

                    return sprite;
                },

                // Copy the Sprite component
                [](const std::shared_ptr<IComponent> &component)->std::shared_ptr<IComponent>
                {
                    auto toCopy = static_cast<Component::Sprite *>(component.get());
                    std::shared_ptr<IComponent> sprite(new Component::Sprite(toCopy->texture, toCopy->rect));

                    return sprite;
                },

                // Copy the Text component
                [](const std::shared_ptr<IComponent> &component)->std::shared_ptr<IComponent>
                {
                    auto toCopy = static_cast<Component::Text *>(component.get());
                    std::shared_ptr<IComponent> text(new Component::Text(toCopy->text));

                    return text;
                },

                // Copy the Text component
                [](const std::shared_ptr<IComponent> &component)->std::shared_ptr<IComponent>
                {
                    auto toCopy = static_cast<Component::Transform *>(component.get());
                    std::shared_ptr<IComponent> transform(new Component::Transform(toCopy->x, toCopy->y, toCopy->z));

                    return transform;
                }
            };
    };
}