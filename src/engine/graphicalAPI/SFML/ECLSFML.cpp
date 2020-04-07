#include "ECLSFML.hpp"

void ECL::ECLSFML::create_window(const ECL::Vector2<std::size_t> &vec, const std::string &name)
{
    _w = std::make_unique<sf::RenderWindow>(sf::VideoMode(vec.x, vec.y), name);
}

void ECL::ECLSFML::draw_entity(const std::shared_ptr<ECS::Entity> &entity)
{
    // Getting the sprite component of the entity.
    if (entity->hasComponent(ECS::Component::Flags::sprite))
    {
        auto component = static_cast<ECS::Component::Sprite *>(entity->component(ECS::Component::Flags::sprite).get());

        // Adding the texture to a sprite pool if it not already exists.
        if (_drawables.find(component->texture) == _drawables.end())
        {
            _drawables.emplace(component->texture, std::make_pair<sf::Texture, sf::Sprite>(
                sf::Texture(),
                sf::Sprite()
            ));
            _drawables[component->texture].first.loadFromFile(component->texture);
            _drawables[component->texture].second.setTexture(_drawables[component->texture].first);
        }

        // Drawing the entity on the window.
        _w->draw(_drawables[component->texture].second);

        // TODO : delete this.
        _w->display();
    }
}

void ECL::ECLSFML::draw_pixel(const ECL::Vector2<std::size_t> &vec, const ECL::Color &color)
{
    (void) vec;
    (void) color;
}