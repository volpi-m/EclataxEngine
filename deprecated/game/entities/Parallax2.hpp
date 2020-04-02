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
    /// \class Parallax2
    /// \brief Parallax for level 2
    class Parallax2 : public IEnnemy
    {
    public:
        /// \brief Constructor
        Parallax2() = default;

        /// \brief Destructor
        ~Parallax2() = default;

        /// \brief Create a parallax2 to be used
        /// \return return a pointer on a Parallax2 entity
        ECS::Entity *createEntity() override;
    };
}

#endif /* !PARALLAX_HPP_ */
