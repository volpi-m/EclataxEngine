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