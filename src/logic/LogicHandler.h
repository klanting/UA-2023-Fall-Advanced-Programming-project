//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_LOGICHANDLER_H
#define PROJECTPACMAN_LOGICHANDLER_H
#include "AbstractFactory.h"
#include "World/World.h"
#include "Controller/MovementController.h"
#include "Controller/Controller.h"
#include "Score.h"
#include "../logic/World/WorldReader.h"
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
        std::unique_ptr<Logic::World> world;
        std::unique_ptr<WorldLoading::WorldLoader> world_loader;
        std::shared_ptr<Score> score;
        std::shared_ptr<Controller::Controller> controller;
        double difficulty_index;
    };

} // Logic

#endif //PROJECTPACMAN_LOGICHANDLER_H
