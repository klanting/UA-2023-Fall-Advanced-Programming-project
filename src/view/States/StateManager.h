//
// Created by tibov on 26/11/23.
//

#ifndef PROJECTPACMAN_STATEMANAGER_H
#define PROJECTPACMAN_STATEMANAGER_H
#include "State.h"
#include <stack>
namespace View {
/**
 * Part of Design pattern: State
 * The statemanager will manage the states
 * */
class StateManager: public std::enable_shared_from_this<StateManager>{
    public:
        explicit StateManager(std::unique_ptr<State> state);
        void Push(std::unique_ptr<State> state);
        void Pop(int amount);
        void acceptCharacter(int input, bool pressed, const Logic::Vector2D<> & v);
        void runTick();


        ~StateManager() = default;
    private:
        std::stack<std::unique_ptr<State>> state_stack;
        bool first_ptr_set;


    };

} // View

#endif //PROJECTPACMAN_STATEMANAGER_H
