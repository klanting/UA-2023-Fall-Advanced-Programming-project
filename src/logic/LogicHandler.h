//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_LOGICHANDLER_H
#define PROJECTPACMAN_LOGICHANDLER_H
#include "AbstractFactory.h"
#include "World.h"
#include "Controller/MovementController.h"
#include "Controller/Controller.h"
#include "Score.h"
namespace Logic {

    class LogicHandler {
    public:
        LogicHandler(std::shared_ptr<AbstractFactory> factory);

        bool doTick();

        const std::shared_ptr<Score> &getScore() const;
        int getLives() const;
        void nextLevel();
        bool isGameOver();
    private:
        std::shared_ptr<AbstractFactory> factory;
        std::unique_ptr<Logic::World> world;
        std::shared_ptr<Score> score;
        std::shared_ptr<Controller::Controller> controller;
        double difficulty_index;
    };

} // Logic

#endif //PROJECTPACMAN_LOGICHANDLER_H
