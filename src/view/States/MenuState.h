//
// Created by tibov on 26/11/23.
//

#ifndef PROJECTPACMAN_MENUSTATE_H
#define PROJECTPACMAN_MENUSTATE_H
#include "State.h"
#include "../RenderWindowSingleton.h"
#include "../UIObjects/StartButton.h"
namespace View {

    class MenuState: public State{
    public:

        MenuState();
        void runTick() override;
        void acceptCharacter(int input, bool pressed, const Logic::Vector2D& v) override;
    private:
        void renderUI() override;
        int animation_index = 0;
        double animation_delay = 0.5;
        sf::Texture texture;
        StartButton play_button;
    };

} // View

#endif //PROJECTPACMAN_MENUSTATE_H
