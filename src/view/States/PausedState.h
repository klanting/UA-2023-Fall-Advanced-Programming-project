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

    /**
     * Part of Design pattern: State
     * Derived class of State
     * Representing the state when we pause the game
     * */
    class PausedState: public State {
    public:
        PausedState();
        void runTick() override;
        void acceptCharacter(int input, bool pressed, const Logic::Vector2D<>& v) override;
    private:
        /**
         * show the home and continue button
         * */
        void renderUI() const override;
        sf::Texture texture;
        ContinueButton continue_button;
        MenuButton home_button;

    };



} // View

#endif //PROJECTPACMAN_PAUSEDSTATE_H
