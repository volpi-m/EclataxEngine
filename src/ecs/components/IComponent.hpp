/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component interface
*/

#pragma once

namespace ECS {

    using flagType = unsigned char;

    namespace Flags {
        typedef enum e_flags {transform, audio, physic, script, life, particules, parallax} flags;
    }

    class IComponent {
    public:
        virtual ~IComponent() = default;

        // template<class ...Args>
        // void update(Args... args) {};
    };
}
