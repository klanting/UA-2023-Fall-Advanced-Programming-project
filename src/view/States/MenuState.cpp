//
// Created by tibov on 26/11/23.
//

#include "MenuState.h"
#include "StateManager.h"
#include "LevelState.h"
namespace View {
    void MenuState::runTick() {

    }

    void MenuState::acceptCharacter(int input, bool pressed) {
        std::cout << "game started" << std::endl;
        if (!pressed){
            return;
        }

        if (state_manager.expired()){
            return;
        }
        state_manager.lock()->Push(std::make_unique<LevelState>());
    }
} // View