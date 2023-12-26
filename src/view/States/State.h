//
// Created by tibov on 26/11/23.
//

#ifndef PROJECTPACMAN_STATE_H
#define PROJECTPACMAN_STATE_H
#include <memory>
#include <iostream>
#include "../RenderWindowSingleton.h"
#include "../Camera.h"
#include "../../logic/Stopwatch.h"
#include "../UIObjects/UIObject.h"
namespace View {
    /**
     * Part of Design pattern: State
     * This class is the Abstract Class for the State design pattern
     * */
    class StateManager;
    class State {
    public:
        /**
         * Constructor for state
         * */
        State() = default;

        /**
         * Destructor for state
         * */
        virtual ~State() = default;

        /**
         * run 1 tick for the state
         * */
        virtual void runTick() = 0;

        /**
         * pass through received input
         * input int gives the value of the input index
         * bool pressed states if it is pressed or released
         * v will give the position on the screen where pressed which is usefull in case of mouse click
         * */
        virtual void acceptCharacter(int input, bool pressed, const Logic::Vector2D<>& v) = 0;

        /**
         * add weakptr to State manager
         * */
        void setManager(std::weak_ptr<StateManager> state_manager);

    protected:
        /**
         * Renders UI components
         * */
        virtual void renderUI() const;

        /**
         * List of UI objects
         * */
        std::vector<std::unique_ptr<UIObject>> render_images;
        std::weak_ptr<StateManager> state_manager;
    };

} // View

#endif //PROJECTPACMAN_STATE_H
