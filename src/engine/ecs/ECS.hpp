/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Game Engine methods
*/

#pragma once

#include <string>
#include <optional>

#include "IComponent.hpp"
#include "IModule.hpp"
#include "ISystem.hpp"
#include "Entity.hpp"

namespace Module {
        
        class EntityComponentSystem : public IModule {
        public:
            EntityComponentSystem() = default;
            ~EntityComponentSystem() = default;

            void update();
            unsigned long long createEntity(const std::string &tag = "");
            unsigned long long createChildEntity(unsigned long long id, const std::string &tag = "");
            void addComponentToEntity(unsigned long long id, std::unique_ptr<ECS::IComponent>);

            void setEntityPosition(unsigned long long id, unsigned int x, unsigned int y);
            void setEntitySpeed(unsigned long long id, unsigned int damage);
            void setEntityDamage(unsigned long long id, unsigned int damage);

            std::optional<unsigned long long> checkCollision(unsigned long long id);
            void hideEntity(unsigned long long id);
            void showEntity(unsigned long long id);

            unsigned long long getTag(unsigned long long id);
            bool isEntityVisible(unsigned long long id);
            //ECS::Entity getEntity(unsigned long long id);

            void entityDebugCollisionBox(unsigned long long id, bool show);
            
            bool isInitialised() override {return false;};
        private:
            void init() override {};
            bool _initialised;

            std::vector<std::unique_ptr<ECS::ISystem>> _systems;
            std::unordered_map<unsigned long long, std::shared_ptr<ECS::Entity>> _entities;
        };
}
