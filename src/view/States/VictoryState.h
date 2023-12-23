//
// Created by tibov on 26/11/23.
//

#ifndef PROJECTPACMAN_VICTORYSTATE_H
#define PROJECTPACMAN_VICTORYSTATE_H
#include "State.h"
#include "../UIObjects/PositionAnimation.h"
#include "../UIObjects/CutOffAnimation.h"
namespace View {

    class VictoryState: public State{
    public:
        VictoryState();
        void runTick() override;
        void acceptCharacter(int input, bool pressed, const Logic::Vector2D& v) override;
    private:
        double key_press_delay = 1;
        sf::Texture texture;

        void createEatAnimation();


    };



} // View

#endif //PROJECTPACMAN_VICTORYSTATE_H
