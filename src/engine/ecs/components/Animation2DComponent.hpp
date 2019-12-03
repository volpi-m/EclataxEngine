/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Component Animation
*/

/// \file Animation.hpp
/// \author Someone
/// \brief AnimationComponent class declaration

#pragma once

#include <chrono>

#include "Rect.hpp"
#include "IComponent.hpp"

/// \namespace ECS
/// \brief Used for the all entity component system subclasses
namespace ECS {
    /// \namespace Component
    /// \brief Used for the all component
    namespace Component {

        /// \struct Animation2D
        /// \brief Animation structure, create the Animation component
        struct Animation2D : public IComponent {
            
            /// \brief constructor
            Animation2D() : lastAnimationTime(std::chrono::high_resolution_clock::now()), animationTime(1000), rect(Game::Rect()), maximumLeft(0), offset(0) {}

            /// \brief constructor
            Animation2D(std::chrono::milliseconds time, Game::Rect &rect, float max, float anim) : lastAnimationTime(std::chrono::high_resolution_clock::now()), animationTime(time), rect(rect), maximumLeft(max), offset(anim) {}

            /*! animation speed attribute */
            std::chrono::high_resolution_clock::time_point lastAnimationTime;

            /*! animation time attribute */
            std::chrono::milliseconds animationTime;

            /*! rectangle attribute */
            Game::Rect rect;

            /*! maximum spritesheet distance attribute */
            float maximumLeft;

            /*! animation offset attribute */
            float offset;
        };
    }
}
