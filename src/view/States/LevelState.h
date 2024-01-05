//
// Created by tibov on 26/11/23.
//

#ifndef PROJECTPACMAN_LEVELSTATE_H
#define PROJECTPACMAN_LEVELSTATE_H
#include "State.h"
#include "../../logic/World/World.h"
#include "../../logic/LogicHandler.h"
namespace View {

    /**
     * Part of Design pattern: State
     * Derived class of State
     * Representing the state when the game is currently active
     * */
    class LevelState: public State{
    public:
        LevelState();
        void runTick() override;
        void acceptCharacter(int input, bool pressed, const Logic::Vector2D<>& v) override;
    private:
        /**
         * this will draw the scores and lives based on the data of the LogicHandler
         * */
        void renderUI() const override;
        std::unique_ptr<Logic::LogicHandler> handler;
        std::weak_ptr<Controller::Controller> controller;

    };


} // View

#endif //PROJECTPACMAN_LEVELSTATE_H
