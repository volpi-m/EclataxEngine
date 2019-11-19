/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component interface
*/

#pragma once

namespace ECS {

    using flagType = unsigned char;

    /// \namespace Component
    /// \brief Used for all the Component subclasses
    namespace Component {
        
        /// \namespace Flags
        /// \brief Flags for components
        namespace Flags {
            typedef enum e_flags {transform, audio, physic, script, health, particules, parallax, sprite, collisionBox} flags;
        }
    }

    class IComponent {
    public:
        virtual ~IComponent() = default;

        // template<class ...Args>
        // void update(Args... args) {};
    };
}
