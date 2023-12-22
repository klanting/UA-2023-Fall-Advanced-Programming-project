//
// Created by tibov on 25/11/23.
//

#include "LogicHandler.h"
#include <iostream>
#include "Stopwatch.h"

namespace Logic {
    LogicHandler::LogicHandler(std::shared_ptr<AbstractFactory> factory): factory{factory} {
        std::cout << "logic handler started" << std::endl;
        //temp concrete factory creating
        Controller::MovementController::getInstance()->clear();
        difficulty_index = 1;
        score = std::make_shared<Score>();
        world = std::make_unique<World>(factory, score, difficulty_index, 3);

    }

    bool LogicHandler::doTick() {

        bool alive = world->doTick();
        Stopwatch::getInstance()->doTick();
        return alive;
    }

    const std::shared_ptr<Score> &LogicHandler::getScore() const {
        return score;
    }

    int LogicHandler::getLives() const {
        return world->getLives();
    }

    void LogicHandler::nextLevel() {
        std::cout << "next lvl created" << std::endl;
        Controller::MovementController::getInstance()->clear();
        difficulty_index += 0.1;
        int remaining_lives = world->getLives();
        world = std::make_unique<World>(factory, score, difficulty_index, remaining_lives);

    }


    bool LogicHandler::isGameOver() {
        return getLives() <= 0;
    }
} // Logic