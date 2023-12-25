//
// Created by tibov on 26/11/23.
//

#ifndef PROJECTPACMAN_GAMEOVERSTATE_H
#define PROJECTPACMAN_GAMEOVERSTATE_H
#include "State.h"
#include "../RenderWindowSingleton.h"
namespace View {

    class GameOverState: public State{
    public:
        GameOverState();
        void runTick() override;
        void acceptCharacter(int input, bool pressed, const Logic::Vector2D<>& v) override;
    private:
        double key_press_delay = 1;
        sf::Texture texture;

        void createGameOverTitle();
        void createGhostAnimation();

    };

} // View

#endif //PROJECTPACMAN_GAMEOVERSTATE_H
