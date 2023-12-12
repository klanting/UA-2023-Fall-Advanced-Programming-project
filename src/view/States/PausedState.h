//
// Created by tibov on 26/11/23.
//

#ifndef PROJECTPACMAN_PAUSEDSTATE_H
#define PROJECTPACMAN_PAUSEDSTATE_H
#include "State.h"
namespace View {

    class PausedState: public State {
    public:
        PausedState() = default;
        void runTick() override;
        void acceptCharacter(int input, bool pressed) override;
    private:
        void renderUI();

    };



} // View

#endif //PROJECTPACMAN_PAUSEDSTATE_H
