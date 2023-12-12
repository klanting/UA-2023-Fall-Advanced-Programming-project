//
// Created by tibov on 26/11/23.
//

#include "VictoryState.h"
#include "StateManager.h"
namespace View {
    void VictoryState::runTick() {
        key_press_delay -= Logic::Stopwatch::getInstance()->getDeltaTime();
        renderUI();
        Logic::Stopwatch::getInstance()->doTick();

    }

    void VictoryState::acceptCharacter(int input, bool pressed) {
        std::cout << "back_to_menu" << std::endl;
        if (!pressed){
            return;
        }

        if (state_manager.expired()){
            return;
        }

        if (key_press_delay > 0){
            return;
        }

        state_manager.lock()->Pop(1);

    }

    void VictoryState::renderUI() {

    }
} // View