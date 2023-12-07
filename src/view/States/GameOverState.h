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
        void acceptCharacter(int input, bool pressed) override;
    private:
        void renderUI();
        int animation_index = 0;
        double animation_delay = 0.25;
        sf::Texture texture;

    };

} // View

#endif //PROJECTPACMAN_GAMEOVERSTATE_H
