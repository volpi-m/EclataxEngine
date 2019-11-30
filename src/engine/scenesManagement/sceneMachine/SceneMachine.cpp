/*
** EPITECH PROJECT, 2019
** SceneMachine.hpp
** File description:
** SceneMachine class
*/

#include "Logger.hpp"
#include "SceneMachine.hpp"

Module::SceneMachine::SceneMachine() {}

Module::SceneMachine::~SceneMachine() {}

void Module::SceneMachine::push(std::shared_ptr<Scenes::IScene> &scene)
{
    if (!_scenes.empty())
        _scenes.top()->setVisible(false);
    _scenes.emplace(scene);
}

void Module::SceneMachine::pop()
{
    if (!_scenes.empty())
        _scenes.pop();
}

void Module::SceneMachine::pop(const std::string &name)
{
    while (!_scenes.empty() && _scenes.top()->name() != name)
        pop();
    if (!_scenes.empty())
        _scenes.top()->setVisible(true);
}

void Module::SceneMachine::pop(const char *name)
{
    while (!_scenes.empty() && _scenes.top()->name() != name)
        pop();
    if (!_scenes.empty())
        _scenes.top()->setVisible(true);
}

void Module::SceneMachine::swap(std::shared_ptr<Scenes::IScene> &scene)
{
    pop();
    push(scene);
}

std::string Module::SceneMachine::name() const
{
    return _scenes.empty() ? "" : _scenes.top()->name();
}

size_t Module::SceneMachine::size() const
{
    return _scenes.empty() ? 0 : _scenes.size();
}

bool Module::SceneMachine::isToPop() const
{
    return _scenes.empty() ? false : _scenes.top()->isToPop();
}

bool Module::SceneMachine::isToSwap() const
{
    return _scenes.empty() ? false : _scenes.top()->isToSwap();
}

bool Module::SceneMachine::run()
{
    Scenes::IScene *newScene = nullptr;

    if ((newScene = _scenes.top()->run())) {
        std::shared_ptr<Scenes::IScene> tmp(newScene);

        if (newScene->isToSwap())
            swap(tmp);
        else
            push(tmp);
    } else if (_scenes.top()->isToPop() && !_scenes.top()->isToSwap()) {
        pop();
        if (!_scenes.empty()) {
            _scenes.top()->setPop(false);
            _scenes.top()->setVisible(true);
    	}
    } else if (_scenes.top()->isToPop() && _scenes.top()->isToSwap())
        pop(_scenes.top()->name());
    return _scenes.size() ? true : false;
}

std::stack<Network::Entity> &Module::SceneMachine::getCurrentSceneEntityStack()
{
    return _scenes.top()->entityStack();
}

void Module::SceneMachine::sendEventsToCurrentScene(std::queue<std::pair<int, size_t>> &events)
{
    _scenes.top()->handleEvent(events);
}
