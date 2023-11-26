//
// Created by tibov on 26/11/23.
//

#ifndef PROJECTPACMAN_MENUSTATE_H
#define PROJECTPACMAN_MENUSTATE_H
#include "State.h"
namespace View {

    class MenuState: public State{
    public:
        MenuState() = default;
        void runTick() override;
        void acceptCharacter(char input) override;
    private:

    };

} // View

#endif //PROJECTPACMAN_MENUSTATE_H
