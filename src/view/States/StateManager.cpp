//
// Created by tibov on 26/11/23.
//

#include "StateManager.h"

namespace View {
    StateManager::StateManager(std::unique_ptr<State> state) {
        state_stack.push(std::move(state));

    }

    void StateManager::Push(std::unique_ptr<State> state) {
        state_stack.push(std::move(state));
    }

    void StateManager::Pop(int amount) {
        for (int i=0; i<amount; i++){
            state_stack.pop();
        }

    }
} // View