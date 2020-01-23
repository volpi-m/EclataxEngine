
#pragma once

#include "IScene.hpp"

namespace Scenes
{

    class AScene : public IScene
    {

        public:

            AScene() = default;

            AScene(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS, std::shared_ptr<Module::IMediator> &mediator);

            void onInit(const std::string &name, std::shared_ptr<Module::EntityComponentSystem> &ECS, std::shared_ptr<Module::IMediator> &mediator) override;

            void setName(const std::string &name) override;

            std::string name() const override;

        protected:

            std::string _name;

            std::shared_ptr<Module::IMediator> _mediator;

            std::shared_ptr<Module::EntityComponentSystem> _ECS;
    };
}