//
// Created by tibov on 26/11/23.
//

#include "LevelState.h"
#include "../ConcreteFactory.h"
namespace View {
    LevelState::LevelState() {
        //temp concrete factory creating
        world = std::make_unique<Logic::World>(std::make_shared<ConcreteFactory>());

    }

    void LevelState::runTick() {

    }

    void LevelState::acceptCharacter(int input) {

    }
} // View