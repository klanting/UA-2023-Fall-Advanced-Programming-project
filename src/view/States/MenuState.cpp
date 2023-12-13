//
// Created by tibov on 26/11/23.
//

#include "MenuState.h"
#include "StateManager.h"
#include "LevelState.h"

#include "../../logic/Stopwatch.h"

#include "../../logic/Vector2D.h"
#include "../Scoreboard.h"
namespace View {
    void MenuState::runTick() {
        renderUI();
        Logic::Stopwatch::getInstance()->doTick();
    }

    void MenuState::acceptCharacter(int input, bool pressed, const Logic::Vector2D& v) {
        std::cout << v[0] << " " << v[1] << std::endl;
        if (input != 0){
            return;
        }

        if (state_manager.expired()){
            return;
        }

        std::cout << "game started" << std::endl;

        if (play_button.isClicked(v)){
            state_manager.lock()->Push(std::make_unique<LevelState>());
        }


    }

    void MenuState::renderUI() {
        double d = Logic::Stopwatch::getInstance()->getDeltaTime();
        animation_delay -= d;
        while (animation_delay < 0){
            animation_index = (animation_index + 1) % 2;
            animation_delay += 0.5;
        }

        std::vector<int> top_positions = {69, (int) (1+animation_index*34), 69+34};
        std::vector<Logic::Vector2D> positions = {Logic::Vector2D{-0.65, -0.8}, Logic::Vector2D{-0.25, -0.8}, Logic::Vector2D{0.0, -0.8}, };
        std::vector<int> heights = {34, 34, 34};
        for (int i =0; i<top_positions.size(); i++){
            std::unique_ptr<sf::Sprite> logo = std::make_unique<sf::Sprite>();
            logo->setTexture(texture);

            logo->setTextureRect(sf::IntRect(1, top_positions[i], 300, heights[i]));

            auto p = Camera::getInstance()->toPixels(positions[i], Logic::Vector2D{0, 0});
            logo->setPosition(p.first[0], p.first[1]);
            logo->setScale((heights[i]/34.0)*RenderWindowSingleton::getInstance()->getSize().x/300.0, (heights[i]/34.0)*RenderWindowSingleton::getInstance()->getSize().y/300.0);

            RenderWindowSingleton::getInstance()->draw_bufferless(std::move(logo));
        }

        play_button.render();
        Scoreboard::getInstance()->render();

    }

    MenuState::MenuState(){
        texture.loadFromFile("sprites/pacman_menu.png", sf::IntRect(0, 0, 300, 500));

        play_button = {Logic::Vector2D{-0.45, 0.5}, Logic::Vector2D{0.91, 0.32}};

    }
} // View