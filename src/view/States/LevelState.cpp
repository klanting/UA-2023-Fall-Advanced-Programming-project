//
// Created by tibov on 26/11/23.
//

#include "LevelState.h"
#include "../ConcreteFactory.h"
namespace View {
    LevelState::LevelState() {
        handler = std::make_unique<Logic::LogicHandler>(std::make_shared<ConcreteFactory>());
        controller = Controller::MovementController::getInstance();

    }

    void LevelState::runTick() {
        handler->doTick();
    }

    void LevelState::acceptCharacter(int input, bool pressed) {
        std::cout << "input: " << input << std::endl;

        switch (input) {
            case 73:
                controller.lock()->moveUp(pressed);
                break;
            case 72:
                controller.lock()->moveRight(pressed);
                break;
            case 71:
                controller.lock()->moveLeft(pressed);
                break;
            case 74:
                controller.lock()->moveDown(pressed);
                break;
        }

    }
} // View