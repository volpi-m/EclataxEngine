/**
 *  @file     src/main.cpp
 *  @author   Arthur Lang on the 2020-03-31
 *  @date     2020-03-31
 * 
 *  project: EclataxEngine
 * 
 */

#include "GameEngine.hpp"
#include "Vector.hpp"
#include "Log.hpp"

int main(int argc, char const **argv)
{
    (void) argc;
    (void) argv;

    // Creatint an engine instance.
    Game::GameEngine engine;

    // Creating an entity.
    auto id = engine.ECS()->createEntity("Square");
    std::shared_ptr<ECS::IComponent> sprite_component = std::make_shared<ECS::Component::Sprite>("../deprecated/ressources/level_2.png", ECL::Rect(100, 100, 100, 100));

    // Adding a sprite component to the entity.
    engine.ECS()->addComponentToEntity(id, ECS::Component::Flags::sprite, sprite_component);

    // Logs
    ECL::Log::get() << ECL::Log::Control::Color << ECL::Log::Control::Time << ECL::Log::Priority::Warning << "Creating an entity 'square'. id: \n" << id << ECL::Log::Control::Flush;
    ECL::Log::get() << ECL::Log::Control::Color << ECL::Log::Control::Time << ECL::Log::Priority::Warning << "Drawing it to the screen\n" << ECL::Log::Control::Flush;

    // Creating a window from the graphical library
    engine.GraphicalAPI()->create_window(ECL::Vector2<std::size_t> { 800, 800 }, "test window");

    // Draw the entity to the screen.
    engine.GraphicalAPI()->draw_entity(engine.ECS()->entity(id));

    // Keeping the window open.
    while (true) {}

    return 0;
}