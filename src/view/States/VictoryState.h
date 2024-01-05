//
// Created by tibov on 26/11/23.
//

#ifndef PROJECTPACMAN_VICTORYSTATE_H
#define PROJECTPACMAN_VICTORYSTATE_H
#include "State.h"
#include "../UIObjects/PositionAnimation.h"
#include "../UIObjects/CutOffAnimation.h"
namespace View {

    /**
     * Part of Design pattern: State
     * Derived class of State
     * Representing the state when the level is finished
     * */
    class VictoryState: public State{
    public:
        VictoryState();
        void runTick() override;
        void acceptCharacter(int input, bool pressed, const Logic::Vector2D<>& v) override;
    private:
        double key_press_delay = 0.4;
        sf::Texture texture;

        /**
         * creates animation where pacman eats the word 'Victory'
         * */
        void createEatAnimation();


    };



} // View

#endif //PROJECTPACMAN_VICTORYSTATE_H
