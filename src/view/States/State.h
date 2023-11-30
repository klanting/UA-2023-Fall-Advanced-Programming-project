//
// Created by tibov on 26/11/23.
//

#ifndef PROJECTPACMAN_STATE_H
#define PROJECTPACMAN_STATE_H
#include <memory>
#include <iostream>
namespace View {
    class StateManager;
    class State {
    public:
        State() = default;
        virtual ~State() = default;
        virtual void runTick() = 0;
        virtual void acceptCharacter(int input, bool pressed) = 0;
        void setManager(std::weak_ptr<StateManager> state_manager);

    protected:
        std::weak_ptr<StateManager> state_manager;
    };

} // View

#endif //PROJECTPACMAN_STATE_H
