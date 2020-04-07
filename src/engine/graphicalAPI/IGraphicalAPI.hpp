/**
 *  @file     src/engine/graphicalAPI/IGraphicalAPI.hpp
 *  @author   ltabis
 *  @date     07/04/2020
 * 
 *  project: EclataxEngine
 * 
 */

#pragma once

#include "Entity.hpp"
#include "Vector.hpp"
#include "Color.hpp"

namespace Module
{

    /**
     *  @class   IGraphicalAPI
     *  @brief   An interface that will be used to render objects on the screen.
     *           Using an interface we can use multiple graphical libraries.
     */
    class IGraphicalAPI
    {

        public:
            virtual ~IGraphicalAPI() = default;

            virtual void create_window(const ECL::Vector2<std::size_t> &vec, const std::string &name) = 0;

            virtual void draw_entity(const std::shared_ptr<ECS::Entity> &entity) = 0;

            virtual void draw_pixel(const ECL::Vector2<std::size_t> &vec, const ECL::Color &color) = 0;
    };
}