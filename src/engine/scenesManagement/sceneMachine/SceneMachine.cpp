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
    _scenes.push(scene);
}

void Module::SceneMachine::pop()
{
    if (!_scenes.empty())
        _scenes.pop();
}

void Module::SceneMachine::pop(const std::string &name)
{
    if (_scenes.empty())
        return;
    while (!_scenes.empty() && _scenes.top()->name() != name)
        pop();
    if (!_scenes.empty())
        _scenes.top()->setVisible(true);
}

void Module::SceneMachine::swap(std::shared_ptr<Scenes::IScene> &scene)
{
    std::string name = _scenes.top()->name();

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

void Module::SceneMachine::run()
{
    if (!_scenes.empty())
        while (_scenes.top()->run());
}