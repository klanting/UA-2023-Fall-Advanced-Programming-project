//
// Created by tibov on 26/11/23.
//

#ifndef PROJECTPACMAN_STATE_H
#define PROJECTPACMAN_STATE_H
#include <memory>
#include <iostream>
namespace View {

    class State {
    public:
        State() = default;
        virtual void runTick() = 0;
        virtual void acceptCharacter(int input) = 0;
    private:
    };

} // View

#endif //PROJECTPACMAN_STATE_H
