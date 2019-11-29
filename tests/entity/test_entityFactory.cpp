//
// Created by tabis on 10/10/2019.
//

#include "EntityFactory.hpp"
#include <gtest/gtest.h>

TEST(EntityFactoryTests, registerEntity)
{
    ECS::EntityFactory factory;
    ECS::Entity entity(std::string("entity from string"));

    ASSERT_EQ(factory.hasEntity("entity1"), false);
    factory.registerEntity("entity1", entity);
    factory.registerEntity("entity1", entity);
    ASSERT_EQ(factory.hasEntity("entity1"), true);
}

TEST(EntityFactoryTests, registerEntityWithComponents)
{
    ECS::EntityFactory factory;
    ECS::Entity entity(std::string("entity from string"));
    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform);
    std::shared_ptr<ECS::IComponent> audio(new ECS::Component::Audio);

    entity.addComponent(ECS::Component::Flags::transform, transform);
    entity.addComponent(ECS::Component::Flags::audio, audio);
    ASSERT_EQ(factory.hasEntity("entity1"), false);
    factory.registerEntity("entity1", entity);
    ASSERT_EQ(factory.hasEntity("entity1"), true);
}

TEST(EntityFactoryTests, registerEntityFromFlags)
{
    ECS::EntityFactory factory;

    // Creating a new entity with 3 blanc components
    factory.registerEntity("new entity", ECS::Component::Flags::collisionBox2D | ECS::Component::Flags::life | ECS::Component::Flags::script);
    factory.registerEntity("new entity", ECS::Component::Flags::collisionBox2D | ECS::Component::Flags::life | ECS::Component::Flags::script);

    ASSERT_EQ(factory.hasEntity("new entity"), true);

    // Creating a new entity from the blueprint
    std::shared_ptr<ECS::Entity> entityCpy = factory.createEntity("new entity");
    std::shared_ptr<ECS::Entity> wrongEntityCpy = factory.createEntity("entity");

    // Wrong entity blueprint name
    ASSERT_EQ(wrongEntityCpy.get(), nullptr);

    // The entity should have been created with all the components specified
    ASSERT_EQ(entityCpy->hasComponent(ECS::Component::Flags::collisionBox2D), true);
    ASSERT_EQ(entityCpy->hasComponent(ECS::Component::Flags::life), true);
    ASSERT_EQ(entityCpy->hasComponent(ECS::Component::Flags::script), true);

    // Checking unspecified components
    ASSERT_EQ(entityCpy->hasComponent(ECS::Component::Flags::speed), false);
    ASSERT_EQ(entityCpy->hasComponent(ECS::Component::Flags::transform), false);
    ASSERT_EQ(entityCpy->hasComponent(ECS::Component::Flags::text), false);
}

TEST(EntityFactoryTests, createEntitiesFromBlueprints)
{
    ECS::EntityFactory factory;
    ECS::Entity entity(std::string("entity from string"));
    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform);
    std::shared_ptr<ECS::IComponent> audio(new ECS::Component::Audio);

    entity.addComponent(ECS::Component::Flags::transform, transform);
    entity.addComponent(ECS::Component::Flags::audio, audio);
    ASSERT_EQ(factory.hasEntity("entity1"), false);
    factory.registerEntity("entity1", entity);
    ASSERT_EQ(factory.hasEntity("entity1"), true);

    std::shared_ptr<ECS::Entity> entityCpy1 = factory.createEntity("entity1");
    std::shared_ptr<ECS::Entity> entityCpy2 = factory.createEntity("entity1");

    // Checking if the components have been copied
    ASSERT_EQ(entityCpy1->hasComponent(ECS::Component::Flags::transform), true);
    ASSERT_EQ(entityCpy1->hasComponent(ECS::Component::Flags::audio), true);
    ASSERT_EQ(entityCpy2->hasComponent(ECS::Component::Flags::transform), true);
    ASSERT_EQ(entityCpy2->hasComponent(ECS::Component::Flags::audio), true);

    // Checking if there are no other components
    ASSERT_EQ(entityCpy1->hasComponent(ECS::Component::Flags::text), false);
    ASSERT_EQ(entityCpy2->hasComponent(ECS::Component::Flags::spawner), false);

    // Check memory, to see if the pointers are all different
    ASSERT_NE(entityCpy1->component(ECS::Component::Flags::transform).get(), entity.component(ECS::Component::Flags::transform).get());
    ASSERT_NE(entityCpy2->component(ECS::Component::Flags::transform).get(), entity.component(ECS::Component::Flags::transform).get());
    ASSERT_NE(entityCpy1->component(ECS::Component::Flags::audio).get(), entity.component(ECS::Component::Flags::audio).get());
    ASSERT_NE(entityCpy2->component(ECS::Component::Flags::audio).get(), entity.component(ECS::Component::Flags::audio).get());
}

TEST(EntityFactoryTests, createEntitiesFromBlueprintsAndCopyStates)
{
    ECS::EntityFactory factory;
    ECS::Entity entity(std::string("entity from string"));
    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform(42, 42, 42));
    std::shared_ptr<ECS::IComponent> audio(new ECS::Component::Audio("file", true));

    entity.addComponent(ECS::Component::Flags::transform, transform);
    entity.addComponent(ECS::Component::Flags::audio, audio);
    ASSERT_EQ(factory.hasEntity("entity1"), false);

    std::shared_ptr<ECS::Entity> entityCpy1 = factory.createEntity(entity, ECS::Component::Flags::transform | ECS::Component::Flags::audio);
    std::shared_ptr<ECS::Entity> entityCpy2 = factory.createEntity(entity, ECS::Component::Flags::transform);

    // Checking if the components have been copied
    ASSERT_EQ(entityCpy1->hasComponent(ECS::Component::Flags::transform), true);
    ASSERT_EQ(entityCpy1->hasComponent(ECS::Component::Flags::audio), true);
    ASSERT_EQ(entityCpy2->hasComponent(ECS::Component::Flags::transform), true);
    ASSERT_EQ(entityCpy2->hasComponent(ECS::Component::Flags::audio), true);

    // Checking if there are no other components
    ASSERT_EQ(entityCpy1->hasComponent(ECS::Component::Flags::text), false);
    ASSERT_EQ(entityCpy2->hasComponent(ECS::Component::Flags::spawner), false);

    // Check memory, to see if the pointers are all different
    ASSERT_NE(entityCpy1->component(ECS::Component::Flags::transform).get(), entity.component(ECS::Component::Flags::transform).get());
    ASSERT_NE(entityCpy2->component(ECS::Component::Flags::transform).get(), entity.component(ECS::Component::Flags::transform).get());
    ASSERT_NE(entityCpy1->component(ECS::Component::Flags::audio).get(), entity.component(ECS::Component::Flags::audio).get());
    ASSERT_NE(entityCpy2->component(ECS::Component::Flags::audio).get(), entity.component(ECS::Component::Flags::transform).get());
    ASSERT_NE(entityCpy1->component(ECS::Component::Flags::transform).get(), entityCpy2->component(ECS::Component::Flags::transform).get());
    ASSERT_NE(entityCpy1->component(ECS::Component::Flags::audio).get(), entityCpy2->component(ECS::Component::Flags::audio).get());

    // Getting the transform component to see if it's attributes have nee copied
    auto componentTransformCpy1 = static_cast<ECS::Component::Transform *>(entityCpy1->component(ECS::Component::Flags::transform).get());

    ASSERT_EQ(componentTransformCpy1->x, 42);
    ASSERT_EQ(componentTransformCpy1->y, 42);
    ASSERT_EQ(componentTransformCpy1->z, 42);

    // Same with the audio
    auto componentAudioCpy1 = static_cast<ECS::Component::Audio *>(entityCpy1->component(ECS::Component::Flags::audio).get());

    ASSERT_STREQ(componentAudioCpy1->file.c_str(), "file");
    ASSERT_EQ(componentAudioCpy1->active, true);

    // Same with the second 
    auto componentTransformCpy2 = static_cast<ECS::Component::Transform *>(entityCpy1->component(ECS::Component::Flags::transform).get());

    ASSERT_EQ(componentTransformCpy2->x, 42);
    ASSERT_EQ(componentTransformCpy2->y, 42);
    ASSERT_EQ(componentTransformCpy2->z, 42);

    // for the audio component, it has been created empty (didn't specified in the flags)
    auto componentAudioCpy2 = static_cast<ECS::Component::Audio *>(entityCpy2->component(ECS::Component::Flags::audio).get());

    ASSERT_STREQ(componentAudioCpy2->file.c_str(), "");
    ASSERT_EQ(componentAudioCpy2->active, false);
}

TEST(EntityFactoryTests, createEntityWithBlanc)
{
    ECS::EntityFactory factory;

    factory.registerEntity("entity1",
                  ECS::Component::Flags::acceleration
                | ECS::Component::Flags::audio
                | ECS::Component::Flags::collisionBox2D
                | ECS::Component::Flags::damage
                | ECS::Component::Flags::health
                | ECS::Component::Flags::life
                | ECS::Component::Flags::particules
                | ECS::Component::Flags::script
                | ECS::Component::Flags::spawner
                | ECS::Component::Flags::speed
                | ECS::Component::Flags::sprite
                | ECS::Component::Flags::text
                | ECS::Component::Flags::transform);
    ASSERT_EQ(factory.hasEntity("entity1"), true);

    auto cpy = factory.createEntity("entity1");
    ASSERT_EQ(cpy->hasComponent(ECS::Component::Flags::acceleration), true);
    ASSERT_EQ(cpy->hasComponent(ECS::Component::Flags::audio), true);
    ASSERT_EQ(cpy->hasComponent(ECS::Component::Flags::collisionBox2D), true);
    ASSERT_EQ(cpy->hasComponent(ECS::Component::Flags::damage), true);
    ASSERT_EQ(cpy->hasComponent(ECS::Component::Flags::health), true);
    ASSERT_EQ(cpy->hasComponent(ECS::Component::Flags::life), true);
    ASSERT_EQ(cpy->hasComponent(ECS::Component::Flags::particules), true);
    ASSERT_EQ(cpy->hasComponent(ECS::Component::Flags::script), true);
    ASSERT_EQ(cpy->hasComponent(ECS::Component::Flags::spawner), true);
    ASSERT_EQ(cpy->hasComponent(ECS::Component::Flags::speed), true);
    ASSERT_EQ(cpy->hasComponent(ECS::Component::Flags::sprite), true);
    ASSERT_EQ(cpy->hasComponent(ECS::Component::Flags::text), true);
    ASSERT_EQ(cpy->hasComponent(ECS::Component::Flags::transform), true);
}

void dummyScript(std::shared_ptr<ECS::Entity> &entity)
{
    entity->setVisible(false);
}

std::shared_ptr<ECS::Entity> dummySpawner(std::shared_ptr<ECS::Entity> &entity)
{
    (void)entity;

    return std::shared_ptr<ECS::Entity>(new ECS::Entity("test"));
}


TEST(EntityFactoryTests, createCopyedComponents)
{
    // Creating all components available
    ECS::EntityFactory factory;
    Game::Rect rect(0, 0, 32, 32);
    std::shared_ptr<ECS::Entity> entity(new ECS::Entity("dummy entity"));
    std::shared_ptr<ECS::IComponent> acceleration(new ECS::Component::Acceleration(5));
    std::shared_ptr<ECS::IComponent> audio(new ECS::Component::Audio("test_file", true));
    std::shared_ptr<ECS::IComponent> collision(new ECS::Component::CollisionBox2D(0, 0, 200, 200));
    std::shared_ptr<ECS::IComponent> damage(new ECS::Component::Damage(15));
    std::shared_ptr<ECS::IComponent> health(new ECS::Component::Health(150));
    std::shared_ptr<ECS::IComponent> life(new ECS::Component::Life(3));
    std::shared_ptr<ECS::IComponent> particules(new ECS::Component::Particules(100, 5, 1));
    std::shared_ptr<ECS::IComponent> script(new ECS::Component::Script(&dummyScript));
    std::shared_ptr<ECS::IComponent> spwaner(new ECS::Component::Spawner(std::chrono::seconds(4), dummySpawner));
    std::shared_ptr<ECS::IComponent> speed(new ECS::Component::Speed(20.5f));
    std::shared_ptr<ECS::IComponent> sprite(new ECS::Component::Sprite("Texture_file.jpg", rect));
    std::shared_ptr<ECS::IComponent> text(new ECS::Component::Text("Text to display"));
    std::shared_ptr<ECS::IComponent> transform(new ECS::Component::Transform(10, 42, 84));

    // Adding components to the entity
    entity->addComponent(ECS::Component::Flags::acceleration, acceleration);
    entity->addComponent(ECS::Component::Flags::audio, audio);
    entity->addComponent(ECS::Component::Flags::collisionBox2D, collision);
    entity->addComponent(ECS::Component::Flags::damage, damage);
    entity->addComponent(ECS::Component::Flags::health, health);
    entity->addComponent(ECS::Component::Flags::life, life);
    entity->addComponent(ECS::Component::Flags::particules, particules);
    entity->addComponent(ECS::Component::Flags::script, script);
    entity->addComponent(ECS::Component::Flags::spawner, spwaner);
    entity->addComponent(ECS::Component::Flags::speed, speed);
    entity->addComponent(ECS::Component::Flags::sprite, sprite);
    entity->addComponent(ECS::Component::Flags::text, text);
    entity->addComponent(ECS::Component::Flags::transform, transform);

    // Checking if all components are there
    ASSERT_EQ(entity->hasComponent(ECS::Component::Flags::acceleration), true);
    ASSERT_EQ(entity->hasComponent(ECS::Component::Flags::audio), true);
    ASSERT_EQ(entity->hasComponent(ECS::Component::Flags::collisionBox2D), true);
    ASSERT_EQ(entity->hasComponent(ECS::Component::Flags::damage), true);
    ASSERT_EQ(entity->hasComponent(ECS::Component::Flags::health), true);
    ASSERT_EQ(entity->hasComponent(ECS::Component::Flags::life), true);
    ASSERT_EQ(entity->hasComponent(ECS::Component::Flags::particules), true);
    ASSERT_EQ(entity->hasComponent(ECS::Component::Flags::script), true);
    ASSERT_EQ(entity->hasComponent(ECS::Component::Flags::spawner), true);
    ASSERT_EQ(entity->hasComponent(ECS::Component::Flags::speed), true);
    ASSERT_EQ(entity->hasComponent(ECS::Component::Flags::sprite), true);
    ASSERT_EQ(entity->hasComponent(ECS::Component::Flags::text), true);
    ASSERT_EQ(entity->hasComponent(ECS::Component::Flags::transform), true);

    // Copying all components of the entity to the copy
    auto copy = factory.createEntity(*(entity.get()),
                  ECS::Component::Flags::acceleration
                | ECS::Component::Flags::audio
                | ECS::Component::Flags::collisionBox2D
                | ECS::Component::Flags::damage
                | ECS::Component::Flags::health
                | ECS::Component::Flags::life
                | ECS::Component::Flags::particules
                | ECS::Component::Flags::script
                | ECS::Component::Flags::spawner
                | ECS::Component::Flags::speed
                | ECS::Component::Flags::sprite
                | ECS::Component::Flags::text
                | ECS::Component::Flags::transform);

    // Getting all the components from the new entity
    auto accelerationC = static_cast<ECS::Component::Acceleration *>(copy->component(ECS::Component::Flags::acceleration).get());
    auto audioC = static_cast<ECS::Component::Audio *>(copy->component(ECS::Component::Flags::audio).get());
    auto collisionBox2DC = static_cast<ECS::Component::CollisionBox2D *>(copy->component(ECS::Component::Flags::collisionBox2D).get());
    auto damageC = static_cast<ECS::Component::Damage *>(copy->component(ECS::Component::Flags::damage).get());
    auto healthC = static_cast<ECS::Component::Health *>(copy->component(ECS::Component::Flags::health).get());
    auto lifeC = static_cast<ECS::Component::Life *>(copy->component(ECS::Component::Flags::life).get());
    auto particulesC = static_cast<ECS::Component::Particules *>(copy->component(ECS::Component::Flags::particules).get());
    auto scriptC = static_cast<ECS::Component::Script *>(copy->component(ECS::Component::Flags::script).get());
    auto spawnerC = static_cast<ECS::Component::Spawner *>(copy->component(ECS::Component::Flags::spawner).get());
    auto speedC = static_cast<ECS::Component::Speed *>(copy->component(ECS::Component::Flags::speed).get());
    auto spriteC = static_cast<ECS::Component::Sprite *>(copy->component(ECS::Component::Flags::sprite).get());
    auto textC = static_cast<ECS::Component::Text *>(copy->component(ECS::Component::Flags::text).get());
    auto transformC = static_cast<ECS::Component::Transform *>(copy->component(ECS::Component::Flags::transform).get());

    // Checking if the components have been copied
    ASSERT_EQ(accelerationC->acceleration, 5);
    ASSERT_STREQ(audioC->file.c_str(), "test_file");
    ASSERT_EQ(audioC->active, true);
    ASSERT_EQ(collisionBox2DC->rectangle.top, 0);
    ASSERT_EQ(collisionBox2DC->rectangle.left, 0);
    ASSERT_EQ(collisionBox2DC->rectangle.width, 200);
    ASSERT_EQ(collisionBox2DC->rectangle.height, 200);
    ASSERT_EQ(damageC->damage, 15);
    ASSERT_EQ(healthC->health, 150);
    ASSERT_EQ(healthC->healthLimit, 0);
    ASSERT_EQ(lifeC->lifes, 3);
    ASSERT_EQ(particulesC->samples, 100);
    ASSERT_EQ(particulesC->size, 5);
    ASSERT_EQ(particulesC->speed, 1);
    ASSERT_EQ(scriptC->updateScript, &dummyScript);
    ASSERT_STREQ(spawnerC->createBlueprint(copy)->tag().c_str(), "test");
    ASSERT_EQ(spawnerC->seconds, std::chrono::seconds(4));
    ASSERT_EQ(speedC->speed, 20);
    ASSERT_EQ(spriteC->loaded, false);
    ASSERT_EQ(spriteC->rect.height, 32);
    ASSERT_EQ(spriteC->rect.width, 32);
    ASSERT_EQ(spriteC->rect.top, 0);
    ASSERT_EQ(spriteC->rect.left, 0);
    ASSERT_STREQ(spriteC->texture.c_str(), "Texture_file.jpg");
    ASSERT_STREQ(textC->text.c_str(), "Text to display");
    ASSERT_EQ(transformC->x, 10);
    ASSERT_EQ(transformC->y, 42);
    ASSERT_EQ(transformC->z, 84);
}