//
// Created by tibov on 26/11/23.
//

#ifndef PROJECTPACMAN_LEVELSTATE_H
#define PROJECTPACMAN_LEVELSTATE_H
#include "State.h"
#include "../../logic/World.h"
#include "../../logic/LogicHandler.h"
namespace View {

    class LevelState: public State{
    public:
        LevelState();
        void runTick() override;
        void acceptCharacter(int input, bool pressed) override;
    private:
        void renderUI() override;
        std::unique_ptr<Logic::LogicHandler> handler;
        std::weak_ptr<Controller::Controller> controller;

    };

} // View

#endif //PROJECTPACMAN_LEVELSTATE_H
