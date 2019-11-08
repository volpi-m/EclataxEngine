/*
** EPITECH PROJECT, 2019
** SceneMachine.hpp
** File description:
** SceneMachine class
*/

#include "Logger.hpp"
#include "SceneMachine.hpp"

indie::SceneMachine *indie::SceneMachine::getInstance()
{
    static auto instance = new SceneMachine;

    return instance;
}

void indie::SceneMachine::push(indie::IScene *scene)
{
    if (!_scenes.empty())
        _scenes.top()->setVisible(false);
    _scenes.push(scene);
}

void indie::SceneMachine::pop()
{
    if (!_scenes.empty()) {
        if (_scenes.top()->getName() != "Start Option Scene")
            _scenes.top()->remove();
        _scenes.pop();
    }
}

void indie::SceneMachine::pop(const std::string &name)
{
    if (_scenes.empty())
        return;
    pop();
    while (!_scenes.empty() && _scenes.top()->getName() != name) {
        if (!_scenes.empty()) {
            if (_scenes.top()->getName() != "Start Option Scene")
                _scenes.top()->remove();
            _scenes.pop();
        }
    }
    if (!_scenes.empty()) {
        _scenes.top()->setPop(false);
        _scenes.top()->setVisible(true);
    }
}

void indie::SceneMachine::swap(indie::IScene *scene)
{
    std::string name = _scenes.top()->getName();

    pop();
    push(scene);
}

std::string indie::SceneMachine::getSceneName() const
{
    if (_scenes.empty())
        return "";
    return _scenes.top()->getName();
}

size_t indie::SceneMachine::size() const
{
    return _scenes.empty() ? 0 : _scenes.size();
}

bool indie::SceneMachine::isToPop() const
{
    return _scenes.empty() ? false : _scenes.top()->isToPop();
}

void indie::SceneMachine::run()
{
    indie::IScene *newScene = nullptr;

    if ((newScene = _scenes.top()->computeEvents())) {
        if (newScene->isToSwap())
            swap(newScene);
        else
            push(newScene);
    } else if (_scenes.top()->isToPop() && !_scenes.top()->isToSwap()) {
        pop();
        if (!_scenes.empty()) {
            _scenes.top()->setPop(false);
            _scenes.top()->setVisible(true);
        }
    } else if (_scenes.top()->isToPop() && _scenes.top()->isToSwap())
        pop(_scenes.top()->getName());
}