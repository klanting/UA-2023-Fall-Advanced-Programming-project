//
// Created by tibov on 26/11/23.
//

#include "VictoryState.h"
#include "StateManager.h"
namespace View {
    void VictoryState::runTick() {
        key_press_delay -= Logic::Stopwatch::getInstance()->getDeltaTime();
        renderUI();
        Logic::Stopwatch::getInstance()->doTick();

    }

    void VictoryState::acceptCharacter(int input, bool pressed, const Logic::Vector2D& v) {
        std::cout << "back_to_menu" << std::endl;
        if (!pressed){
            return;
        }

        if (state_manager.expired()){
            return;
        }

        if (key_press_delay > 0){
            return;
        }

        state_manager.lock()->Pop(1);

    }

    void VictoryState::renderUI() {
        std::vector<int> top_positions = {301, 69+70+18+18};
        std::vector<Logic::Vector2D> positions = {Logic::Vector2D{-0.52, -0.4}, Logic::Vector2D{-0.7, 0.0}};
        std::vector<int> heights = {34, 17};
        for (int i =0; i<top_positions.size(); i++){
            std::unique_ptr<sf::Sprite> logo = std::make_unique<sf::Sprite>();
            logo->setTexture(texture);

            logo->setTextureRect(sf::IntRect(0, top_positions[i], 500, heights[i]));

            auto p = Camera::getInstance()->toPixels(positions[i], Logic::Vector2D{0, 0});
            logo->setPosition(p.first[0], p.first[1]);

            double multiply = 1;
            if (i == 0){
                multiply = 0.8;
            }

            logo->setScale(multiply*(heights[i]/34.0)*RenderWindowSingleton::getInstance()->getSize().x/300.0, multiply*(heights[i]/34.0)*RenderWindowSingleton::getInstance()->getSize().y/300.0);

            RenderWindowSingleton::getInstance()->draw_bufferless(std::move(logo));
        }

    }

    VictoryState::VictoryState() {
        texture.loadFromFile("sprites/pacman_menu.png", sf::IntRect(0, 0, 500, 500));

    }
} // View