//
// Created by tibov on 25/11/23.
//

#include "LogicHandler.h"
#include <iostream>
#include "Stopwatch.h"
namespace Logic {
    LogicHandler::LogicHandler(std::shared_ptr<AbstractFactory> factory) {
        std::cout << "logic handler started" << std::endl;
        //temp concrete factory creating
        Stopwatch::getInstance();
        Controller::MovementController::getInstance();
        world = std::make_unique<World>(factory);

    }

    void LogicHandler::doTick() {

        world->doTick();
        Stopwatch::getInstance()->doTick();
    }
} // Logic