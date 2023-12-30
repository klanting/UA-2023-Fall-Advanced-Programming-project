//
// Created by tibov on 26/11/23.
//

#ifndef PROJECTPACMAN_GAME_H
#define PROJECTPACMAN_GAME_H
#include <SFML/Graphics.hpp>
#include <memory>
#include "States/StateManager.h"
#include "States/MenuState.h"
#include "RenderWindowSingleton.h"
#include <ctime>
namespace View {
    /**
     * This Class will setup the SFMl LOOP
     * */
    class Game {
    public:
        Game();
    private:
        std::shared_ptr<RenderWindowSingleton> window;
        std::shared_ptr<StateManager> state_manager;
        void doGameLoop();

        /**
         * on input key this function will be called, and this will call a function of the state manager
         * */
    };

} // View

#endif //PROJECTPACMAN_GAME_H
