//
// Created by tibov on 26/11/23.
//

#include "MenuState.h"
#include "StateManager.h"
#include "LevelState.h"
namespace View {
    void MenuState::runTick() {

    }

    void MenuState::acceptCharacter(int input) {
        std::cout << "game started" << std::endl;
        state_manager->Push(std::make_unique<LevelState>());
    }
} // View