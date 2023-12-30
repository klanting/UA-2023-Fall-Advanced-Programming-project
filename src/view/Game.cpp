//
// Created by tibov on 26/11/23.
//

#include "Game.h"
#include "States/GameOverState.h"
using namespace std;
namespace View {
    typedef sf::RenderWindow RW;
    Game::Game() {
        window = RenderWindowSingleton::getInstance();
        state_manager = make_shared<StateManager>(make_unique<MenuState>());
        doGameLoop();
    }

    void Game::doGameLoop() {

        while (window->isOpen())
        {

            state_manager->checkInput();


            window->clear();
            state_manager->runTick();

            window->display();

            sf::sleep(sf::milliseconds(15));

        }

    }

} // View