//
// Created by tibov on 26/11/23.
//

#ifndef PROJECTPACMAN_PAUSEDSTATE_H
#define PROJECTPACMAN_PAUSEDSTATE_H
#include "State.h"
#include "../UIObjects/StartButton.h"
#include "../UIObjects/ContinueButton.h"
#include "../UIObjects/MenuButton.h"
namespace View {

    class PausedState: public State {
    public:
        PausedState();
        void runTick() override;
        void acceptCharacter(int input, bool pressed, const Logic::Vector2D& v) override;
    private:
        void renderUI();
        sf::Texture texture;
        ContinueButton continue_button;
        MenuButton home_button;

    };



} // View

#endif //PROJECTPACMAN_PAUSEDSTATE_H
