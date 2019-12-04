/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component interface
*/

#pragma once

namespace ECS
{
    using flagType = int;

    /// \namespace Component
    /// \brief Used for all the Component subclasses
    namespace Component
    {
        /// \namespace Flags
        /// \brief Flags for components
        namespace Flags
        {
            typedef enum e_flags {transform = 1,
                                  audio = 2,
                                  physic = 4,
                                  script = 8,
                                  health = 16,
                                  particules = 32,
                                  parallax = 64,
                                  sprite = 128,
                                  collisionBox2D = 256,
                                  spawner = 512,
                                  acceleration = 1024,
                                  damage = 2048,
                                  life = 4096,
                                  speed = 8192,
                                  text = 16384,
                                  animation2D = 32768,
                                  lifeSpan = 65536
            } flags;
        }
    }

    /// \class IComponent
    /// \brief virtual class used to story all component in an entity in a single
    /// container class
    class IComponent
    {
    public:
        virtual ~IComponent() = default;
    };
}
