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

    void PausedState::acceptCharacter(int input, bool pressed, const Logic::Vector2D<>& v) {

        if (state_manager.expired()){
            throw std::bad_weak_ptr();
        }

        if (input == 0){
            //go back to LevelState
            if (continue_button->isClicked(v)){
                state_manager.lock()->Pop(1);
                return;
            }

            //go back to menuState
            if (home_button->isClicked(v)){
                state_manager.lock()->Pop(2);
            }
            return;
        }

        if (!pressed){
            return;
        }

        state_manager.lock()->Pop(1);
    }



    PausedState::PausedState() {
        texture.loadFromFile("sprites/pacman_menu.png", sf::IntRect(0, 0, 450, 500));

        //create the buttons
        continue_button = std::make_shared<ContinueButton>(Logic::Vector2D{-0.175, -0.1}, Logic::Vector2D{0.35, 0.32});
        home_button = std::make_shared<MenuButton>(Logic::Vector2D{0.6, 0.65}, Logic::Vector2D{0.35, 0.32});

        render_images.push_back(continue_button);
        render_images.push_back(home_button);

        //create the Paused text
        std::shared_ptr<sf::Sprite> paused_text = std::make_shared<sf::Sprite>();
        paused_text->setTextureRect(sf::IntRect(1, 404, 500, 34));

        std::unique_ptr<Image> img = std::make_unique<Image>(Logic::Vector2D<>{-0.85, -0.8}, Logic::Vector2D<>{1.67, 0.18}, Logic::Vector2D<>{315, 34}, paused_text, texture);

        render_images.push_back(std::move(img));

    }

}