//
// Created by tibov on 26/11/23.
//

#include "PausedState.h"
#include "StateManager.h"
namespace View {
    void PausedState::runTick() {
        renderUI();
        Logic::Stopwatch::getInstance()->doTick();

    }

    void PausedState::acceptCharacter(int input, bool pressed, const Logic::Vector2D& v) {

        if (state_manager.expired()){
            return;
        }

        if (input == 0){
            if (continue_button.isClicked(v)){
                state_manager.lock()->Pop(1);
            }

            if (home_button.isClicked(v)){
                state_manager.lock()->Pop(2);
            }
        }

        if (!pressed){
            return;
        }

        state_manager.lock()->Pop(2);
    }

    void PausedState::renderUI() {

        std::vector<int> top_positions = {404, 69+70+18};
        std::vector<Logic::Vector2D> positions = {Logic::Vector2D{-0.85, -0.8}, Logic::Vector2D{-0.5, 0}};
        std::vector<int> heights = {34, 17};
        for (int i =0; i<top_positions.size(); i++){
            std::unique_ptr<sf::Sprite> logo = std::make_unique<sf::Sprite>();
            logo->setTexture(texture);

            logo->setTextureRect(sf::IntRect(1, top_positions[i], 450, heights[i]));

            auto p = Camera::getInstance()->toPixels(positions[i], Logic::Vector2D{0, 0});
            logo->setPosition(p.first[0], p.first[1]);

            double multiply = 1;
            if (i == 0){
                multiply = 0.8;
            }

            logo->setScale(multiply*(heights[i]/34.0)*RenderWindowSingleton::getInstance()->getSize().x/300.0, multiply*(heights[i]/34.0)*RenderWindowSingleton::getInstance()->getSize().y/300.0);

            RenderWindowSingleton::getInstance()->draw_bufferless(std::move(logo));
        }

        continue_button.render();
        home_button.render();

    }

    PausedState::PausedState() {
        texture.loadFromFile("sprites/pacman_menu.png", sf::IntRect(0, 0, 450, 500));

        continue_button = {Logic::Vector2D{-0.45, 0.5}, Logic::Vector2D{0.91, 0.32}};
        home_button = {Logic::Vector2D{-0.95, 0.5}, Logic::Vector2D{0.91, 0.32}};

    }
}