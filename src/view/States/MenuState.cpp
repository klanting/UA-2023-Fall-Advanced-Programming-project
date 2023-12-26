//
// Created by tibov on 26/11/23.
//

#include "MenuState.h"
#include "StateManager.h"
#include "LevelState.h"


#include "../Scoreboard.h"
namespace View {
    void MenuState::runTick() {
        renderUI();
        Logic::Stopwatch::getInstance()->doTick();
    }

    void MenuState::acceptCharacter(int input, bool pressed, const Logic::Vector2D<>& v) {
        if (input != 0){
            return;
        }

        if (state_manager.expired()){
            return;
        }


        if (play_button->isClicked(v)){
            state_manager.lock()->Push(std::make_unique<LevelState>());
        }


    }

    void MenuState::renderUI() const{

        State::renderUI();

        Scoreboard::getInstance()->render();

    }

    MenuState::MenuState(){
        texture.loadFromFile("sprites/pacman_menu.png", sf::IntRect(0, 0, 300, 500));

        play_button = std::make_shared<StartButton>(Logic::Vector2D{-0.45, 0.5}, Logic::Vector2D{0.91, 0.32});
        render_images.push_back(play_button);

        createPacmanText();
        createPacmanTitleAnimation();
    }

    void MenuState::createPacmanTitleAnimation() {
        std::vector<std::unique_ptr<Image>> images;
        std::vector<int> top_positions = {(1+0*34), (1+1*34)};
        for (int top_position : top_positions){
            std::shared_ptr<sf::Sprite> pacman_anim = std::make_shared<sf::Sprite>();
            pacman_anim->setTextureRect(sf::IntRect(1, top_position, 300, 34));

            std::unique_ptr<Image> img = std::make_unique<Image>(Logic::Vector2D<>{-0.25, -0.8}, Logic::Vector2D<>{0.25, 0.25}, Logic::Vector2D<>{34, 34}, pacman_anim, texture);

            images.push_back(std::move(img));
        }

        std::shared_ptr<ImageAnimation> img_anim = std::make_shared<ImageAnimation>(0.5, std::move(images));
        render_images.push_back(img_anim);

    }

    void MenuState::createPacmanText() {
        std::vector<int> top_positions = {69, 69+34};
        std::vector<Logic::Vector2D<>> positions = {Logic::Vector2D{-0.65, -0.8}, Logic::Vector2D{0.0, -0.8}, };
        std::vector<int> heights = {34, 34};
        for (int i =0; i<top_positions.size(); i++){
            std::shared_ptr<sf::Sprite> logo = std::make_unique<sf::Sprite>();
            logo->setTextureRect(sf::IntRect(1, top_positions[i], 300, heights[i]));

            std::shared_ptr<Image> img = std::make_shared<Image>(positions[i], Logic::Vector2D<>{0.8, 0.25}, Logic::Vector2D<>{103, (double) heights[i]}, logo, texture);

            render_images.push_back(img);
        }

    }
} // View