//
// Created by tibov on 26/11/23.
//

#ifndef PROJECTPACMAN_MENUSTATE_H
#define PROJECTPACMAN_MENUSTATE_H
#include "State.h"
#include "../RenderWindowSingleton.h"
namespace View {

    class MenuState: public State{
    public:

        MenuState();
        void runTick() override;
        void acceptCharacter(int input, bool pressed) override;
    private:
        void renderUI();
        int animation_index = 0;
        double animation_delay = 0.5;
        sf::Texture texture;

    };

} // View

#endif //PROJECTPACMAN_MENUSTATE_H
