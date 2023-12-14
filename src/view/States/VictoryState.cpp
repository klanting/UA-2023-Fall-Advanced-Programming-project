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
        double d = Logic::Stopwatch::getInstance()->getDeltaTime();
        animation_delay -= d;
        while (animation_delay < 0){
            animation_index = (animation_index + 1) % 2;
            animation_delay += 0.25;
            animation_position += 0.05*animation_direction;
            if (animation_position*animation_direction > 0.7 - 0.2*animation_direction){
                animation_direction *= -1;
                //animation_position = -0.8;
            }
        }

        std::vector<int> top_positions = {301, 69+70+18+18, 336+animation_index*34};
        std::vector<Logic::Vector2D> positions = {Logic::Vector2D{-0.42+std::max((animation_position+0.65), 0.0), -0.4}, Logic::Vector2D{-0.7, 0.0}, Logic::Vector2D{animation_position+0.1, -0.42}};

        std::vector<int> heights = {34, 17, 34};

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

    }

    VictoryState::VictoryState() {
        texture.loadFromFile("sprites/pacman_menu.png", sf::IntRect(0, 0, 500, 500));

    }
} // View