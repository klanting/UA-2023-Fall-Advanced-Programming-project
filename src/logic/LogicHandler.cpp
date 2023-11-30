//
// Created by tibov on 25/11/23.
//

#include "LogicHandler.h"
#include <iostream>
namespace Logic {
    LogicHandler::LogicHandler(std::shared_ptr<AbstractFactory> factory) {
        std::cout << "logic handler started" << std::endl;
        //temp concrete factory creating
        world = std::make_unique<World>(factory);
        controller = std::make_shared<Controller::MovementController>();

    }

    std::weak_ptr<Controller::Controller> LogicHandler::getController() const {
        return controller;
    }
} // Logic