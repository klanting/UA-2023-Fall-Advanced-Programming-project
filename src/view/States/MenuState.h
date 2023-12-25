//
// Created by tibov on 26/11/23.
//

#ifndef PROJECTPACMAN_MENUSTATE_H
#define PROJECTPACMAN_MENUSTATE_H
#include "State.h"
#include "../RenderWindowSingleton.h"
#include "../UIObjects/StartButton.h"
#include "../UIObjects/ImageAnimation.h"
namespace View {

    class MenuState: public State{
    public:

        MenuState();
        void runTick() override;
        void acceptCharacter(int input, bool pressed, const Logic::Vector2D<>& v) override;
    private:
        void renderUI() override;
        sf::Texture texture;
        StartButton play_button;

        void createPacmanTitleAnimation();
        void createPacmanText();
    };

} // View

#endif //PROJECTPACMAN_MENUSTATE_H
