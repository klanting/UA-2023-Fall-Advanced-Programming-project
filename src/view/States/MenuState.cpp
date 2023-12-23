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
        play_button.render();

        for (auto& img: render_images){
            img->render();
        }

        Scoreboard::getInstance()->render();

    }

    MenuState::MenuState(){
        texture.loadFromFile("sprites/pacman_menu.png", sf::IntRect(0, 0, 300, 500));

        play_button = {Logic::Vector2D{-0.45, 0.5}, Logic::Vector2D{0.91, 0.32}};

        createPacmanText();
        createPacmanTitleAnimation();
    }

    void MenuState::createPacmanTitleAnimation() {
        std::vector<std::unique_ptr<Image>> images;
        std::vector<int> top_positions = {(1+0*34), (1+1*34)};
        for (int i =0; i<top_positions.size(); i++){
            std::shared_ptr<sf::Sprite> pacman_anim = std::make_shared<sf::Sprite>();
            pacman_anim->setTextureRect(sf::IntRect(1, top_positions[i], 300, 34));

            std::unique_ptr<Image> img = std::make_unique<Image>(Logic::Vector2D{-0.25, -0.8}, Logic::Vector2D{0.25, 0.25}, Logic::Vector2D{34, 34}, pacman_anim, texture);

            images.push_back(std::move(img));
        }

        std::unique_ptr<ImageAnimation> img_anim = std::make_unique<ImageAnimation>(0.5, std::move(images));
        render_images.push_back(std::move(img_anim));

    }

    void MenuState::createPacmanText() {
        std::vector<int> top_positions = {69, 69+34};
        std::vector<Logic::Vector2D> positions = {Logic::Vector2D{-0.65, -0.8}, Logic::Vector2D{0.0, -0.8}, };
        std::vector<int> heights = {34, 34};
        for (int i =0; i<top_positions.size(); i++){
            std::shared_ptr<sf::Sprite> logo = std::make_unique<sf::Sprite>();
            logo->setTextureRect(sf::IntRect(1, top_positions[i], 300, heights[i]));

            std::unique_ptr<Image> img = std::make_unique<Image>(positions[i], Logic::Vector2D{0.8, 0.25}, Logic::Vector2D{103, (double) heights[i]}, logo, texture);

            render_images.push_back(std::move(img));
        }

    }
} // View