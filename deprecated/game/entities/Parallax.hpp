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
    /// \brief Parallax entity for level 1
    class Parallax : public IEnnemy
    {
    public:
        ///\brief Constructor
        Parallax() = default;

        /// \brief Destructor
        ~Parallax() = default;

        /// \brief Create a parallax to be used
        /// \return a pointer on a parallax object
        ECS::Entity *createEntity() override;

    private:
        /// \brief IA function of this entity
        /// \param entity : shared pointer on an instance of Parallax to be used
        static void IA(std::shared_ptr<ECS::Entity> &entity);
    };
}

#endif /* !PARALLAX_HPP_ */
