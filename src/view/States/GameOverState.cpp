

#include "GameOverState.h"
#include "StateManager.h"
#include "MenuState.h"
namespace View {
    void GameOverState::runTick() {
        key_press_delay -= Logic::Stopwatch::getInstance()->getDeltaTime();
        renderUI();
        Logic::Stopwatch::getInstance()->doTick();
    }

    void GameOverState::acceptCharacter(int input, bool pressed, const Logic::Vector2D<>& v) {
        if (!pressed){
            return;
        }

        if (state_manager.expired()){
            throw std::bad_weak_ptr();
        }

        if (key_press_delay > 0){
            return;
        }

        state_manager.lock()->Pop(2);
    }



    GameOverState::GameOverState() {
        texture.loadFromFile("sprites/pacman_menu.png", sf::IntRect(0, 0, 300, 300));

        createGhostAnimation();
        createGameOverTitle();

    }

    void GameOverState::createGameOverTitle() {
        std::vector<int> top_positions = {69+124, 69+70+18};
        std::vector<Logic::Vector2D<>> positions = {Logic::Vector2D{-0.9, -0.3}, Logic::Vector2D<>{-0.5, 0}};
        std::vector<int> heights = {34, 17};
        std::vector<double> scalar = {1, 0.25};
        for (int i =0; i<top_positions.size(); i++){
            std::shared_ptr<sf::Sprite> logo = std::make_shared<sf::Sprite>();
            logo->setTextureRect(sf::IntRect(1, top_positions[i], 300, heights[i]));

            std::shared_ptr<Image> img = std::make_shared<Image>(positions[i], Logic::Vector2D{0.23*scalar[i], 0.23*scalar[i]}, Logic::Vector2D{(double) heights[i], (double) heights[i]}, logo, texture);

            render_images.push_back(img);
        }

    }

    void GameOverState::createGhostAnimation() {
        std::vector<std::unique_ptr<Image>> images;
        std::vector<int> top_positions = {(69+160+0*36), (69+160+1*36)};

        Logic::Vector2D size{0.22, 0.22};

        for (int top_position : top_positions){
            std::shared_ptr<sf::Sprite> pacman_anim = std::make_unique<sf::Sprite>();
            pacman_anim->setTextureRect(sf::IntRect(1, top_position, 300, 34));

            std::unique_ptr<Image> img = std::make_unique<Image>(Logic::Vector2D<>{0.07, -0.3}, size, Logic::Vector2D<>{34, 34}, pacman_anim, texture);

            images.push_back(std::move(img));
        }

        std::shared_ptr<ImageAnimation> img_anim = std::make_shared<ImageAnimation>(0.5, std::move(images));
        render_images.push_back(img_anim);

    }
} // View