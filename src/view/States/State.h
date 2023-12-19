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
    class StateManager;
    class State {
    public:
        State() = default;
        virtual ~State() = default;
        virtual void runTick() = 0;
        virtual void acceptCharacter(int input, bool pressed, const Logic::Vector2D& v) = 0;
        void setManager(std::weak_ptr<StateManager> state_manager);

    protected:
        virtual void renderUI() = 0;
        std::vector<std::unique_ptr<UIObject>> render_images;
        std::weak_ptr<StateManager> state_manager;
    };

} // View

#endif //PROJECTPACMAN_STATE_H
