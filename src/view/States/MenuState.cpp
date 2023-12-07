//
// Created by tibov on 26/11/23.
//

#include "MenuState.h"
#include "StateManager.h"
#include "LevelState.h"

#include "../../logic/Stopwatch.h"
#include "../Camera.h"
#include "../../logic/Vector2D.h"
namespace View {
    void MenuState::runTick() {
        renderUI();
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

    void MenuState::renderUI() {
        double d = Logic::Stopwatch::getInstance()->getDeltaTime();
        animation_delay -= d;
        while (animation_delay < 0){
            animation_index = (animation_index + 1) % 2;
            animation_delay += 0.5;
        }

        std::vector<int> top_positions = {69, (int) (1+animation_index*34), 69+34, 69+70};
        std::vector<Logic::Vector2D> positions = {Logic::Vector2D{-0.65, -0.6}, Logic::Vector2D{-0.25, -0.6}, Logic::Vector2D{0.0, -0.6}, Logic::Vector2D{-0.45, 0}};
        std::vector<int> heights = {34, 34, 34, 17};
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

    MenuState::MenuState() {
        texture.loadFromFile("sprites/pacman_menu.png", sf::IntRect(0, 0, 300, 300));
    }
} // View