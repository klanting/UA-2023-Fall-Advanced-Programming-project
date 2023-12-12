//
// Created by tibov on 26/11/23.
//

#include "PausedState.h"
#include "StateManager.h"
namespace View {
    void PausedState::runTick() {
        Logic::Stopwatch::getInstance()->doTick();

    }

    void PausedState::acceptCharacter(int input, bool pressed) {
        if (!pressed){
            return;
        }

        if (state_manager.expired()){
            return;
        }
        state_manager.lock()->Pop(1);

    }

    void PausedState::renderUI() {

    }
}