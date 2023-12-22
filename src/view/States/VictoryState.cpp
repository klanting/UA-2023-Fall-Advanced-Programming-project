//
// Created by tibov on 26/11/23.
//

#include "VictoryState.h"
#include "StateManager.h"
#include "../UIObjects/Image.h"

namespace View {
    void VictoryState::runTick() {
        key_press_delay -= Logic::Stopwatch::getInstance()->getDeltaTime();
        renderUI();
        Logic::Stopwatch::getInstance()->doTick();

    }

    void VictoryState::acceptCharacter(int input, bool pressed, const Logic::Vector2D& v) {
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
        double d = Logic::Stopwatch::getInstance()->getDeltaTime();
        animation_delay -= d;
        while (animation_delay < 0){
            animation_index = (animation_index + 1) % 2;
            animation_delay += 0.25;
            animation_position += 0.05*animation_direction;
            if (animation_position*animation_direction > 0.7 - 0.2*animation_direction){
                animation_direction *= -1;
            }
        }

        std::vector<int> top_positions = {301, 336+animation_index*34};
        std::vector<Logic::Vector2D> positions = {Logic::Vector2D{-0.42+std::max((animation_position+0.65), 0.0), -0.4}, Logic::Vector2D{animation_position+0.1, -0.42}};

        std::vector<int> heights = {34, 34};

        for (int i =0; i<top_positions.size(); i++){
            std::shared_ptr<sf::Sprite> logo = std::make_shared<sf::Sprite>();
            logo->setTexture(texture);

            int left = 1;
            double multiply = 1;
            if (i == 0){
                multiply = 0.8;

                left += std::max((int)((animation_position+0.65)*190), 0);
            }

            logo->setTextureRect(sf::IntRect(left, top_positions[i], 500, heights[i]));

            auto p = Camera::getInstance()->toPixels(positions[i], Logic::Vector2D{0, 0});

            logo->setPosition(p.first[0], p.first[1]);



            logo->setScale(multiply*(heights[i]/34.0)*RenderWindowSingleton::getInstance()->getSize().x/300.0, multiply*(heights[i]/34.0)*RenderWindowSingleton::getInstance()->getSize().y/300.0);

            RenderWindowSingleton::getInstance()->draw_bufferless(logo);
        }

        for (auto& img: render_images){
            img->render();
        }

    }

    VictoryState::VictoryState() {
        texture.loadFromFile("sprites/pacman_menu.png", sf::IntRect(0, 0, 500, 500));

        std::shared_ptr<sf::Sprite> any_key_message = std::make_shared<sf::Sprite>();
        any_key_message->setTextureRect(sf::IntRect(1, 69+70+18+18, 500, 17));

        std::unique_ptr<Image> img = std::make_unique<Image>(Logic::Vector2D{-0.7, 0.0}, Logic::Vector2D{1.33, 0.06}, Logic::Vector2D{402, 17}, any_key_message, texture);

        render_images.push_back(std::move(img));

        createEatAnimation();

    }

    void VictoryState::createEatAnimation() {
        std::shared_ptr<sf::Sprite> pacman_anim = std::make_shared<sf::Sprite>();
        pacman_anim->setTextureRect(sf::IntRect(1, 336, 500, 34));

        std::vector<std::unique_ptr<Image>> images;

        std::unique_ptr<Image> img = std::make_unique<Image>(Logic::Vector2D{-0.9, -0.42}, Logic::Vector2D{0.25, 0.25}, Logic::Vector2D{34, 34}, pacman_anim, texture);
        images.push_back(std::move(img));

        std::unique_ptr<PositionAnimation> pos_anim = std::make_unique<PositionAnimation>(0.25, std::move(images), Logic::Vector2D{-0.9, -0.42}, Logic::Vector2D{0.6, -0.42});
        render_images.push_back(std::move(pos_anim));

    }
} // View