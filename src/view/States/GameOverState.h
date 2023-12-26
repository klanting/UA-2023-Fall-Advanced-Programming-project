//
// Created by tibov on 26/11/23.
//

#ifndef PROJECTPACMAN_GAMEOVERSTATE_H
#define PROJECTPACMAN_GAMEOVERSTATE_H
#include "State.h"
#include "../RenderWindowSingleton.h"
namespace View {

    /**
     * Part of Design pattern: State
     * Derived class of State
     * Representing the State when the game is over
     * */
    class GameOverState: public State{
    public:
        GameOverState();
        void runTick() override;
        void acceptCharacter(int input, bool pressed, const Logic::Vector2D<>& v) override;
    private:
        /**
         * ensures that users need to wait 1 second before any key press is registered
         * */
        double key_press_delay = 1;
        sf::Texture texture;

        /**
         * Creates the visual text GAME VER
         * */
        void createGameOverTitle();

        /**
         * Create a fun Ghost on the O spot of the text
         * */
        void createGhostAnimation();

    };

} // View

#endif //PROJECTPACMAN_GAMEOVERSTATE_H
