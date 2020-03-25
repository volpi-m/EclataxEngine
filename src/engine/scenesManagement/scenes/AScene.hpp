
#pragma once

#include "IScene.hpp"

namespace Scenes
{

    class AScene : public IScene
    {

        public:

            AScene() = default;

            ~AScene() override = default;

            void onInit(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS, Module::IMediator *mediator) override;

            void setName(const std::string &name) override;

            std::string name() const override;

        protected:

            std::string _name;

            Module::IMediator *_mediator;

            std::shared_ptr<Module::EntityComponentSystem> _ECS;
    };
}