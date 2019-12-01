/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Parallax
*/

#ifndef PARALLAX_HPP_
#define PARALLAX_HPP_

#include <cmath>
#include <random>

#include "IEnnemy.hpp"
#include "SpeedComponent.hpp"
#include "AudioComponent.hpp"
#include "DamageComponent.hpp"
#include "HealthComponent.hpp"
#include "ScriptComponent.hpp"
#include "SpriteComponent.hpp"
#include "TransformComponent.hpp"
#include "Animation2DComponent.hpp"
#include "CollisionBox2DComponent.hpp"
#include "LifeSpanComponent.hpp"

namespace Game
{
    /// \class Parallax
    /// \brief YES
    class Parallax : public IEnnemy
    {
    public:
        Parallax() = default;
        ~Parallax() = default;

        ECS::Entity *createEntity() override;

    private:
        static void IA(std::shared_ptr<ECS::Entity> &entity);
    };
}

#endif /* !PARALLAX_HPP_ */
