//
// Created by tibov on 26/11/23.
//

#ifndef PROJECTPACMAN_VICTORYSTATE_H
#define PROJECTPACMAN_VICTORYSTATE_H
#include "State.h"
namespace View {

    class VictoryState: public State{
    public:
        VictoryState() = default;
        void runTick() override;
        void acceptCharacter(char input) override;
    private:

    };

} // View

#endif //PROJECTPACMAN_VICTORYSTATE_H
