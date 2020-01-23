/**
 *  @file     src/engine/sceneManagment/sceneMachine/SceneStateMachine.hpp
 *  @author   tabis on the 2020-01-22
 *  @date     2020-01-22
 * 
 *  project: EclataxEngine
 * 
 */

#pragma once

#include <unordered_map>
#include <functional>
#include <memory>
#include <string>
#include <chrono>
#include <stack>

#include "IScene.hpp"

namespace Module
{

    /// @enum scene_behavior
    /// @brief States sent to the mediator via the notifie method
    enum scene_state
    {
        POP,
        SWAP,
        PUSH
    };

    class IMediator
    {
    public:
        /** 
         * @brief notify the mediator that a scenes changed it's state
         * @param sender : the scene that called the notify method.
         * @param state : state of the scene
         * @param new_scene : potential new scene to push in case of a swap
         */
        virtual void notify(Scenes::IScene *sender, scene_state state, Scenes::IScene *new_scene) = 0;
    };

    class SceneStateMachine : public IMediator
    {
    public:

        // Ctor / Dtor
        /** 
         * @brief SceneStateMachine
         * Constructor That initialize callbacks
         */
        SceneStateMachine();

        /** 
         * @brief SceneStateMachine
         * Destructor that deletes the content of the scene stack.
         */
        ~SceneStateMachine();

        // Interface
        /** 
         * @brief notify the mediator that a scenes changed it's state
         * @param sender : the scene that called the notify method.
         * @param state : state of the scene
         * @param new_scene : potential new scene to push in case of a swap
         */
        void notify(Scenes::IScene *sender, scene_state state, Scenes::IScene *new_scene) override;

        // Running
        /** 
         * @brief Updates the scene on top of the stack
         * @return true if the action was successful, false otherwise
         */
        bool update();

        // Memory modification        
        /** 
         * @brief Push a scene onto the stack 
         * @param scene : the scene to push
         */
        void push(std::shared_ptr<Scenes::IScene> &scene);
        
        /** 
         * @brief Swap the scene on top of the stack with the scene passed as parameter.
         * @param scene : the scene that will be on top of the stack.
         */
        void swap(std::shared_ptr<Scenes::IScene> &scene);

        /** 
         * @brief Pop scenes until the scene name has been reached.
         * @param name : the name of the scene to stop to.
         */
        void pop(const std::string &name);

        /** 
         * @brief Pop the scene on top of the stack.
         */
        void pop();        
                
        /** 
         * @brief Clear all scenes from the stack.
         */
        void clear();

        /** 
         * @brief Set the name of the scene on top of the stack.
         * @param name : new name of the scene on top of the stack.
         */
        void setName(const std::string &name);

        // Getters
        /** 
         * @brief Get the size of the stack.
         * @return the size of the stack.
         */
        std::size_t size() const;

        /** 
         * @brief Get the name of the scene on top of the stack.
         * @return the name of the scene on top of the stack.
         */
        std::string name() const;

        /** 
         * @brief Check if the stack is empty.
         * @return true if the stack is empty, false otherwise.
         */
        bool empty() const;
        
    private:

        /** 
         * @brief When the mediator is notified via the POP state, pops the scene on top of the stack.
         * @param sender : the scene that notified the mediator.
         * @param scene : Unused parameter.
         */
        void popCallback(Scenes::IScene *sender, Scenes::IScene *scene);

        /** 
         * @brief When the mediator is notified via the SWAP state, swaps the scene on top of the stack.
         * @param sender : the scene that notified the mediator.
         * @param scene : the scene to swap.
         */
        void swapCallback(Scenes::IScene *sender, Scenes::IScene *scene);

        /** 
         * @brief When the mediator is notified via the PUSH state, push a new scene on top of the stack an deactivate the sender.
         * @param sender : the scene that notified the mediator.
         * @param scene : the scene to swap.
         */
        void pushCallback(Scenes::IScene *sender, Scenes::IScene *scene);

        /*! the stack of scenes */
        std::stack<std::shared_ptr<Scenes::IScene>> _scenes;

        /*! using callbacks via the states of the scenes */
        std::unordered_map<scene_state, std::function<void(SceneStateMachine &, Scenes::IScene *, Scenes::IScene *)>> _callbacks;

        /*! time since execution */
        float _deltaTime;
   };
}