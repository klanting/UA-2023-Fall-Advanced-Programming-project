//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_LOGICHANDLER_H
#define PROJECTPACMAN_LOGICHANDLER_H
#include "AbstractFactory.h"
#include "World.h"
#include "Controller/MovementController.h"
#include "Controller/Controller.h"
namespace Logic {

    class LogicHandler {
    public:
        LogicHandler(std::shared_ptr<AbstractFactory> factory);

        std::weak_ptr<Controller::Controller> getController() const;

    private:
        std::unique_ptr<Logic::World> world;
        std::shared_ptr<Controller::Controller> controller;
    };

} // Logic

#endif //PROJECTPACMAN_LOGICHANDLER_H
