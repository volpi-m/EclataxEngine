//
// Created by tabis on 09/10/2019.
//

#include "SceneStateMachine.hpp"

Module::SceneStateMachine::SceneStateMachine(std::shared_ptr<Module::EntityComponentSystem> &ECS)
    : _deltaTime { std::chrono::high_resolution_clock::now().time_since_epoch().count() }
    , _ECS       { ECS                                                                  }
{
    _callbacks.emplace(POP, &SceneStateMachine::popCallback);
    _callbacks.emplace(SWAP, &SceneStateMachine::swapCallback);
    _callbacks.emplace(PUSH, &SceneStateMachine::pushCallback);
}

void Module::SceneStateMachine::notify(Scenes::IScene *sender, Module::scene_state state, Scenes::IScene *new_scene)
{
    (this->*_callbacks[state])(sender, new_scene);
}

bool Module::SceneStateMachine::update()
{
    _deltaTime = std::chrono::high_resolution_clock::now().time_since_epoch().count() - _deltaTime;

    if (!empty())
    {
        _scenes.top()->onUpdate(_deltaTime);
        return true;
    }
    return false;
}

void Module::SceneStateMachine::push(std::shared_ptr<Scenes::IScene> &scene)
{
    // Deactivating the last scene before pushing a new one.
    if (!empty())
        _scenes.top()->onDeactivate();
    
    // Getting a reference to the object, but only in the form of the IMediator interface, to restrain access to the mediators methods.
    IMediator *self(this);

    // Pushing the new scene and call the onCreate() method.
    _scenes.push(scene);
    _scenes.top()->onInit(scene->name(), _ECS, self);
    _scenes.top()->onCreate();
}

void Module::SceneStateMachine::swap(std::shared_ptr<Scenes::IScene> &scene)
{
    // poping the current scene if the stack isn't empty.
    if (!empty())
        pop();

    // Pushing the new scene and call the onCreate() method.
    // We can't use the push() method because it could modify the scene before the one to be swaped.
    _scenes.push(scene);
    _scenes.top()->onCreate();
}

void Module::SceneStateMachine::pop(const std::string &name)
{
    // Poping the scenes until the name is reached.
    while (!empty() && _scenes.top()->name() != name)
    {
        _scenes.top()->onDestroy();
        _scenes.pop();
    }

    // Activating the last scene if the stack isn't empty.
    if (!empty())
        _scenes.top()->onActivate();
}

void Module::SceneStateMachine::pop()
{
    if (!empty())
    {
        // Destroying the scene and poping it.
        _scenes.top()->onDestroy();
        _scenes.pop();

        // If there is still a scene on the stack, activating it.
        if (!empty())
            _scenes.top()->onActivate();
    }
}

void Module::SceneStateMachine::clear()
{
    // Poping all scenes unitil there is nothing left.
    while (!empty())
        pop();
}

void Module::SceneStateMachine::setName(const std::string &name)
{
    if (!empty())
        _scenes.top()->setName(name);
}

std::size_t Module::SceneStateMachine::size() const
{
    return _scenes.size();
}

std::string Module::SceneStateMachine::name() const
{
    return !empty() ? _scenes.top()->name() : "";
}

bool Module::SceneStateMachine::empty() const
{
    return _scenes.empty();
}

void Module::SceneStateMachine::popCallback(Scenes::IScene *sender, Scenes::IScene *scene)
{
    (void) sender;
    (void) scene;

    pop();
}

void Module::SceneStateMachine::swapCallback(Scenes::IScene *sender, Scenes::IScene *scene)
{
    if (!sender || !scene)
        return;

    // Transforming pointer into a shared one.
    std::shared_ptr<Scenes::IScene> ptr(scene);
    swap(ptr);
}

void Module::SceneStateMachine::pushCallback(Scenes::IScene *sender, Scenes::IScene *scene)
{
    if (!sender || !scene)
        return;

    // Transforming pointer into a shared one.
    std::shared_ptr<Scenes::IScene> ptr(scene);
    push(ptr);
}