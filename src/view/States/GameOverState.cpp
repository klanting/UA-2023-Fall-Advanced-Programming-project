//
// Created by tibov on 26/11/23.
//

#include "GameOverState.h"
#include "../../logic/Stopwatch.h"
#include "../Camera.h"
#include "StateManager.h"
#include "MenuState.h"
namespace View {
    void GameOverState::runTick() {
        key_press_delay -= Logic::Stopwatch::getInstance()->getDeltaTime();
        renderUI();
    }

    void GameOverState::acceptCharacter(int input, bool pressed) {
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

        state_manager.lock()->Pop(2);
    }

    void GameOverState::renderUI() {
        double d = Logic::Stopwatch::getInstance()->getDeltaTime();
        animation_delay -= d;
        while (animation_delay < 0){
            animation_index = (animation_index + 1) % 2;
            animation_delay += 0.25;
        }

        std::vector<int> top_positions = {69+124, 69+160+animation_index*36, 69+70+18};
        std::vector<Logic::Vector2D> positions = {Logic::Vector2D{-0.9, -0.3}, Logic::Vector2D{0.05, -0.3}, Logic::Vector2D{-0.5, 0}};
        std::vector<int> heights = {34, 34, 17};
        for (int i =0; i<top_positions.size(); i++){
            std::unique_ptr<sf::Sprite> logo = std::make_unique<sf::Sprite>();
            logo->setTexture(texture);

            logo->setTextureRect(sf::IntRect(1, top_positions[i], 300, heights[i]));

            auto p = Camera::getInstance()->toPixels(positions[i], Logic::Vector2D{0, 0});
            logo->setPosition(p.first[0], p.first[1]);
            logo->setScale((heights[i]/34.0)*RenderWindowSingleton::getInstance()->getSize().x/300.0, (heights[i]/34.0)*RenderWindowSingleton::getInstance()->getSize().y/300.0);

            RenderWindowSingleton::getInstance()->draw_bufferless(std::move(logo));
        }


        Logic::Stopwatch::getInstance()->doTick();

    }

    GameOverState::GameOverState() {
        texture.loadFromFile("sprites/pacman_menu.png", sf::IntRect(0, 0, 300, 300));

    }
} // View