//
// Created by tibov on 26/11/23.
//

#ifndef PROJECTPACMAN_GAMEOVERSTATE_H
#define PROJECTPACMAN_GAMEOVERSTATE_H
#include "State.h"
namespace View {

    class GameOverState: public State{
    public:
        GameOverState() = default;
        void runTick() override;
        void acceptCharacter(int input) override;
    private:

    };

} // View

#endif //PROJECTPACMAN_GAMEOVERSTATE_H
