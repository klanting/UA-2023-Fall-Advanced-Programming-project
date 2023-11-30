//
// Created by tibov on 26/11/23.
//

#ifndef PROJECTPACMAN_STATEMANAGER_H
#define PROJECTPACMAN_STATEMANAGER_H
#include "State.h"
#include <stack>
namespace View {

    class StateManager{
    public:
        StateManager(std::unique_ptr<State> state);
        void Push(std::unique_ptr<State> state);
        void Pop(int amount);
        void acceptCharacter(int input);

        void selfPointer(std::weak_ptr<StateManager> state_manager);

        ~StateManager() = default;
    private:
        std::stack<std::unique_ptr<State>> state_stack;
        std::weak_ptr<StateManager> state_manager;


    };

} // View

#endif //PROJECTPACMAN_STATEMANAGER_H
