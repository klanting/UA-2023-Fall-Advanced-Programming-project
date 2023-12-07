//
// Created by tibov on 26/11/23.
//

#include "MenuState.h"
#include "StateManager.h"
#include "LevelState.h"
#include "../RenderWindowSingleton.h"

namespace View {
    void MenuState::runTick() {
        sf::Text title;

        sf::Font font;
        font.loadFromFile("arial.ttf");
        title.setFont(font);

        title.setString("Pacman");
        title.setCharacterSize(100);
        title.setFillColor(sf::Color{255, 255, 0});
        title.setPosition(100, 100);
        title.setStyle(sf::Text::Bold);

        RenderWindowSingleton::getInstance()->getWindow()->draw(title);




    }

    void MenuState::acceptCharacter(int input, bool pressed) {
        std::cout << "game started" << std::endl;
        if (!pressed){
            return;
        }

        if (state_manager.expired()){
            return;
        }
        state_manager.lock()->Push(std::make_unique<LevelState>());
    }
} // View