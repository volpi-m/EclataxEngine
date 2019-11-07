/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component interface
*/

#pragma once

namespace ECS {

    class IComponent {
    public:
        virtual ~IComponent() = default;

        // template<class ...Args>
        // void update(Args... args) {};
    };
}
