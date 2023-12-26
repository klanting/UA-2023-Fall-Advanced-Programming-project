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

    void VictoryState::acceptCharacter(int input, bool pressed, const Logic::Vector2D<>& v) {
        if (!pressed){
            return;
        }

        if (state_manager.expired()){
            throw std::bad_weak_ptr();
        }

        if (key_press_delay > 0){
            return;
        }

        state_manager.lock()->Pop(1);

    }


    VictoryState::VictoryState() {
        texture.loadFromFile("sprites/pacman_menu.png", sf::IntRect(1, 0, 500, 500));

        std::shared_ptr<sf::Sprite> any_key_message = std::make_shared<sf::Sprite>();
        any_key_message->setTextureRect(sf::IntRect(1, 69+70+18+18, 500, 17));

        std::unique_ptr<Image> img = std::make_unique<Image>(Logic::Vector2D<>{-0.7, 0.0}, Logic::Vector2D<>{1.33, 0.06}, Logic::Vector2D<>{402, 17}, any_key_message, texture);

        render_images.push_back(std::move(img));

        createEatAnimation();

    }

    void VictoryState::createEatAnimation() {
        std::vector<std::unique_ptr<Image>> images;
        for (int  i= 0; i<2; i++){
            std::shared_ptr<sf::Sprite> pacman_anim = std::make_shared<sf::Sprite>();
            pacman_anim->setTextureRect(sf::IntRect(1, 336+i*34, 500, 34));

            std::unique_ptr<Image> img = std::make_unique<Image>(Logic::Vector2D<>{-0.9, -0.42}, Logic::Vector2D<>{0.25, 0.25}, Logic::Vector2D<>{34, 34}, pacman_anim, texture);
            images.push_back(std::move(img));
        }


        std::unique_ptr<PositionAnimation> pos_anim = std::make_unique<PositionAnimation>(0.25, std::move(images), Logic::Vector2D<>{-0.8, -0.42}, Logic::Vector2D<>{0.6, -0.42});


        std::shared_ptr<sf::Sprite> victory_img = std::make_shared<sf::Sprite>();
        victory_img->setTextureRect(sf::IntRect(1, 301, 500, 34));

        images.clear();
        std::unique_ptr<Image> img = std::make_unique<Image>(Logic::Vector2D<>{-0.42, -0.4}, Logic::Vector2D<>{0.98, 0.18}, Logic::Vector2D<>{184, 34}, victory_img, texture);
        images.push_back(std::move(img));

        std::unique_ptr<CutOffAnimation> vic_anim = std::make_unique<CutOffAnimation>(0.25, std::move(images), 1.05, 2, 0.05);

        render_images.push_back(std::move(vic_anim));
        render_images.push_back(std::move(pos_anim));

    }
} // View