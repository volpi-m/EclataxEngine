//
// Created by tabis on 10/10/2019.
//

#include <gtest/gtest.h>

#include "SceneStateMachine.hpp"
#include "Logger.hpp"
#include "AScene.hpp"

class SampleScene : public Scenes::AScene
{
public:
	SampleScene() : Scenes::AScene() {};

	~SampleScene() = default;

	void onUpdate(float deltaTime) override
		{
			(void) deltaTime;
			Debug::Logger::printDebug(Debug::INFO, "The SampleScene is being updated.", "SampleScene::update()");

			IScene *newscene = new SampleScene;
			newscene->setName("NewSampleScene");

			_mediator->notify(this, Module::PUSH, newscene);
			_mediator->notify(nullptr, Module::PUSH, nullptr);
		}

	void onCreate() override
		{
			Debug::Logger::printDebug(Debug::INFO, "onCreate method called.", "SampleScene::onCreate()");
		}

	void onDestroy() override
		{
			Debug::Logger::printDebug(Debug::INFO, "onDestroy method called.", "SampleScene::onDestroy()");
		}

	void onActivate() override
		{
			Debug::Logger::printDebug(Debug::INFO, "onActivate method called.", "SampleScene::onActivate()");
		}

	void onDeactivate() override
		{
			Debug::Logger::printDebug(Debug::INFO, "onDeactivate method called.", "SampleScene::onDeactivate()");
		}
};

TEST(SceneStateMachineTests, SceneStateMachine_basic_methods)
{
    // Creating a new scene state machine, casting it into the IMediator interface.
    std::shared_ptr<Module::EntityComponentSystem> ECS(new Module::EntityComponentSystem);
	std::shared_ptr<Module::SceneStateMachine> machine(new Module::SceneStateMachine(ECS));

    // The interface is used to notify the scene manager that a scene stoped running.
	std::shared_ptr<Scenes::IScene> scene(new SampleScene);

    // No scenes to update, return false.
	ASSERT_EQ(machine->update(), false);

    // Adding a scene to the machine.
	machine->push(scene);

    // The manager has one scene in memory.
    ASSERT_EQ(machine->size(), 1);

    // Changing the scene's name.
	machine->setName("Scene name changed!");
	ASSERT_EQ(machine->name(), "Scene name changed!");

    // Clearing the machine.
	machine->clear();

    // Has the machine been cleared ?
    ASSERT_EQ(machine->size(), 0);
}

TEST(SceneStateMachineTests, SceneStateMachine_scene_manipulation)
{
    // Creating a new scene state machine, casting it into the IMediator interface.
    std::shared_ptr<Module::EntityComponentSystem> ECS = std::make_shared<Module::EntityComponentSystem>();
	std::shared_ptr<Module::SceneStateMachine> machine(new Module::SceneStateMachine(ECS));
	std::shared_ptr<Module::IMediator> ptr(machine);

    // The interface is used to notify the scene manager that a scene stoped running.
	std::shared_ptr<Scenes::IScene> scene1(new SampleScene);
	std::shared_ptr<Scenes::IScene> scene2(new SampleScene);

	scene1->setName("SampleScene1");
	scene2->setName("SampleScene2");

    // No scenes to update, return false.
	ASSERT_EQ(machine->update(), false);

    // Adding scenes to the machine.
	machine->push(scene1);
	machine->push(scene2);

    // The manager has two scenes in memory, updating the first one.
    ASSERT_EQ(machine->size(), 2);

	// Checking the name of the scene on the top of the stack.
    ASSERT_EQ(machine->name(), "SampleScene2");

	// Poping the second scene.
	machine->pop();
    ASSERT_EQ(machine->name(), "SampleScene1");
    ASSERT_EQ(machine->size(), 1);

    // Clearing the machine.
	machine->clear();

    // Has the machine been cleared ?
    ASSERT_EQ(machine->size(), 0);
}

TEST(SceneStateMachineTests, SceneStateMachine_advanced_scene_manipulation)
{
    // Creating a new scene state machine, casting it into the IMediator interface.
    std::shared_ptr<Module::EntityComponentSystem> ECS = std::make_shared<Module::EntityComponentSystem>();
	std::shared_ptr<Module::SceneStateMachine> machine(new Module::SceneStateMachine(ECS));
	std::shared_ptr<Module::IMediator> ptr(machine);

    // The interface is used to notify the scene manager that a scene stoped running.
	std::shared_ptr<Scenes::IScene> scene1(new SampleScene);
	std::shared_ptr<Scenes::IScene> scene2(new SampleScene);

	scene1->setName("SampleScene1");
	scene2->setName("SampleScene2");

    // No scenes to update, return false.
	ASSERT_EQ(machine->update(), false);

    // Adding scenes to the machine.
	machine->push(scene1);

    // The manager has one scene in memory, updating it.
    ASSERT_EQ(machine->size(), 1);

	// Checking the name of the scene on the top of the stack.
    ASSERT_EQ(machine->name(), "SampleScene1");

	// Swaping.
	machine->swap(scene2);
    ASSERT_EQ(machine->name(), "SampleScene2");
    ASSERT_EQ(machine->size(), 1);

	// Push scenes one again.
	machine->push(scene1);
	machine->push(scene2);

	// Poping via string.
	machine->pop("SampleScene1");

	// The pop stopped at SampleScene1.
    ASSERT_EQ(machine->size(), 2);
    ASSERT_EQ(machine->name(), "SampleScene1");

	// Poping via string.
	machine->pop("unknown");

	// There isn't any scenes that are called "unknown" so everything as been poped.
    ASSERT_EQ(machine->size(), 0);
}

class Notify : public Scenes::AScene
{
public:
	Notify() : AScene() {}

	void onUpdate(float deltaTime) override
		{
			(void) deltaTime;

			Debug::Logger::printDebug(Debug::INFO, "The Notify is being updated, poping the scene.", "Notify::update()");

			// calling the mediator for the sake of the example.
			_mediator->notify(this, Module::POP, nullptr);
		}

	void onCreate() override
		{
			Debug::Logger::printDebug(Debug::INFO, "onCreate method called.", "Notify::onCreate()");
		}

	void onDestroy() override
		{
			Debug::Logger::printDebug(Debug::INFO, "onDestroy method called.", "Notify::onDestroy()");
		}

	void onActivate() override
		{
			Debug::Logger::printDebug(Debug::INFO, "onActivate method called.", "Notify::onActivate()");

			// Swaping, for the sake of the example.
			_mediator->notify(this, Module::SWAP, nullptr);

			Scenes::IScene *scene(new SampleScene);
			scene->setName("Notify");
			_mediator->notify(this, Module::SWAP, scene);
		}

	void onDeactivate() override
		{
			Debug::Logger::printDebug(Debug::INFO, "onDeactivate method called.", "Notify::onDeactivate()");
		}
};


TEST(SceneStateMachineTests, SceneStateMachine_notify)
{
    // Creating a new scene state machine, casting it into the IMediator interface.
    std::shared_ptr<Module::EntityComponentSystem> ECS = std::make_shared<Module::EntityComponentSystem>();
	std::shared_ptr<Module::SceneStateMachine> machine(new Module::SceneStateMachine(ECS));
	std::shared_ptr<Module::IMediator> ptr(machine);

    // The interface is used to notify the scene manager that a scene stoped running.
	std::shared_ptr<Scenes::IScene> scene(new Notify);
	std::shared_ptr<Scenes::IScene> sampleScene(new SampleScene);

	scene->setName("Notify");
	sampleScene->setName("SampleScene");

    // No scenes to update, return false.
	ASSERT_EQ(machine->update(), false);

    // Adding a scene to the machine.
	machine->push(scene);

    // The manager has one scene in memory, updating it.
    ASSERT_EQ(machine->size(), 1);
	ASSERT_EQ(machine->update(), true);

	// The scene should have notified the mediator to pop it.
    ASSERT_EQ(machine->size(), 0);

    // Re-adding a scene to the machine.
	machine->push(scene);
    ASSERT_EQ(machine->size(), 1);
    ASSERT_EQ(machine->name(), "Notify");

    // Re-adding a scene to the machine.
	machine->push(sampleScene);
    ASSERT_EQ(machine->size(), 2);

	// Using the PUSH method of the notify method via update.
	machine->update();

	// Checking if a new scene has been added.
    ASSERT_EQ(machine->size(), 3);
    ASSERT_EQ(machine->name(), "NewSampleScene");
}