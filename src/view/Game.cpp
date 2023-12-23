//
// Created by tibov on 26/11/23.
//

#include "Game.h"
#include <iostream>
#include "States/VictoryState.h"
#include "States/GameOverState.h"
using namespace std;
namespace View {
    typedef sf::RenderWindow RW;
    Game::Game() {
        window = RenderWindowSingleton::getInstance();
        state_manager = make_shared<StateManager>(make_unique<VictoryState>());
        doGameLoop();
    }

    void Game::doGameLoop() {

        while (window->isOpen())
        {

            sf::Event event;
            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonPressed){
                    bool pressed = event.type == sf::Event::KeyPressed;
                    processInput(event.key.code, pressed, Logic::Vector2D{(double) event.mouseButton.x, (double) event.mouseButton.y});
                }


                if (event.type == sf::Event::Closed){
                    window->close();
                }

            }

            window->clear();

            state_manager->runTick();

            window->display();

            //sf::sleep(sf::milliseconds(33));

        }

    }

    void Game::processInput(int input, bool pressed, const Logic::Vector2D& v) {
        state_manager->acceptCharacter(input, pressed, v);
    }
} // View