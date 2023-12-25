//
// Created by tibov on 26/11/23.
//

#include "LevelState.h"
#include "../ConcreteFactory.h"
#include "StateManager.h"
#include "GameOverState.h"
#include "PausedState.h"
#include "VictoryState.h"
#include "../Scoreboard.h"
namespace View {
    LevelState::LevelState() {
        handler = std::make_unique<Logic::LogicHandler>(std::move(std::make_unique<ConcreteFactory>()));
        controller = Controller::Controller::getInstance();

    }

    void LevelState::runTick() {
        renderUI();
        bool playable = handler->doTick();
        if (playable){
            return;
        }

        if (state_manager.expired()){
            return;
        }



        if (!handler->isGameOver()){

            state_manager.lock()->Push(std::make_unique<VictoryState>());
            handler->nextLevel();

        }else{
            state_manager.lock()->Push(std::make_unique<GameOverState>());
            Scoreboard::getInstance()->add(handler->getScore()->getScore());
        }

    }

    void LevelState::acceptCharacter(int input, bool pressed, const Logic::Vector2D<>& v) {

        if (state_manager.expired()){
            return;
        }

        switch (input) {
            case 73:
                controller.lock()->moveUp(pressed);
                break;
            case 72:
                controller.lock()->moveRight(pressed);
                break;
            case 71:
                controller.lock()->moveLeft(pressed);
                break;
            case 74:
                controller.lock()->moveDown(pressed);
                break;
            case 36:
                if (!pressed){
                    return;
                }

                std::cout << "Paused" << std::endl;
                state_manager.lock()->Push(std::make_unique<PausedState>());
                break;
        }

    }

    void LevelState::renderUI() {
        std::unique_ptr<sf::Text> score = std::make_unique<sf::Text>();
        sf::Font font;
        font.loadFromFile("arial.ttf");
        score->setString("Score: "+std::to_string(handler->getScore()->getScore()));
        score->setFont(font);
        score->setCharacterSize(50);
        score->setFillColor(sf::Color{255, 255, 0});

        auto p = Camera::getInstance()->toPixels(Vector2D<>{-0.9, 0.2}, Vector2D<>{0, 0});

        score->setPosition(p.first[0], p.first[1]);

        RenderWindowSingleton::getInstance()->draw_bufferless(std::move(score));

        std::unique_ptr<sf::Text> lives = std::make_unique<sf::Text>();

        lives->setString("Lives: "+std::to_string(handler->getLives()));
        lives->setFont(font);
        lives->setCharacterSize(50);
        lives->setFillColor(sf::Color{255, 255, 0});

        p = Camera::getInstance()->toPixels(Vector2D<>{-0.9, 0.4}, Vector2D<>{0, 0});

        lives->setPosition(p.first[0], p.first[1]);

        RenderWindowSingleton::getInstance()->draw_bufferless(std::move(lives));
    }


} // View