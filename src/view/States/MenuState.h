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

    /**
     * Part of Design pattern: State
     * Derived class of State
     * Representing the state when the game is not yet started
     * */
    class MenuState: public State{
    public:

        MenuState();
        void runTick() override;
        void acceptCharacter(int input, bool pressed, const Logic::Vector2D<>& v) override;
    private:
        void renderUI() const override;
        sf::Texture texture;
        std::shared_ptr<StartButton> play_button;

        /**
         * creates the animated C of pacman
         * */
        void createPacmanTitleAnimation();
        /**
         * creates the text PA MAN
         * */
        void createPacmanText();
    };

} // View

#endif //PROJECTPACMAN_MENUSTATE_H
