//
// Created by tibov on 26/11/23.
//

#include "StateManager.h"

namespace View {
    StateManager::StateManager(std::unique_ptr<State> state) {
        //state->setManager(std::shared_ptr<StateManager>(this));
        state_stack.push(std::move(state));

    }

    void StateManager::Push(std::unique_ptr<State> state) {
        state->setManager(std::shared_ptr<StateManager>(this));
        state_stack.push(std::move(state));
    }

    void StateManager::Pop(int amount) {
        for (int i=0; i<amount; i++){
            state_stack.pop();
        }

    }

    void StateManager::acceptCharacter(int input) {
        state_stack.top()->acceptCharacter(input);

    }

    void StateManager::selfPointer(std::shared_ptr<StateManager> state_manager) {
        StateManager::state_manager = state_manager;
        state_stack.top()->setManager(StateManager::state_manager);
    }
} // View