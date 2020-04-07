#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>

#include "IGraphicalAPI.hpp"
#include "SpriteComponent.hpp"

namespace ECL
{
    class ECLSFML : public Module::IGraphicalAPI
    {

        public:
            ~ECLSFML() = default;
                
            void create_window(const ECL::Vector2<std::size_t> &vec, const std::string &name) override;

            void draw_entity(const std::shared_ptr<ECS::Entity> &entity) override;

            void draw_pixel(const ECL::Vector2<std::size_t> &vec, const ECL::Color &color) override;

        private:
            std::unique_ptr<sf::RenderWindow> _w;

            std::unordered_map<std::string, std::pair<sf::Texture, sf::Sprite>> _drawables;
    };
}