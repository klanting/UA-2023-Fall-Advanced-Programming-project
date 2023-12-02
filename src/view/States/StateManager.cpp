//
// Created by tibov on 26/11/23.
//

#include "StateManager.h"

namespace View {
    StateManager::StateManager(std::unique_ptr<State> state) {
        first_ptr_set = false;
        state_stack.push(std::move(state));

    }

    void StateManager::Push(std::unique_ptr<State> state) {
        state->setManager(weak_from_this());
        state_stack.push(std::move(state));
    }

    void StateManager::Pop(int amount) {
        for (int i=0; i<amount; i++){
            state_stack.pop();
        }

    }

    void StateManager::acceptCharacter(int input, bool pressed) {
        if (!first_ptr_set){
            state_stack.top()->setManager(weak_from_this());
            first_ptr_set = true;
        }

        state_stack.top()->acceptCharacter(input, pressed);

    }

    void StateManager::runTick() {
        if (!first_ptr_set){
            state_stack.top()->setManager(weak_from_this());
            first_ptr_set = true;
        }

        state_stack.top()->runTick();
    }


} // View