

#include "Scoreboard.h"
#include <algorithm>
#include "Camera.h"
#include "RenderWindowSingleton.h"
#include <iostream>
namespace View {

    void Scoreboard::render() const{

        sf::Font font;
        bool suc6 = font.loadFromFile("arial.ttf");
        if (!suc6){
            throw std::invalid_argument("arial.ttf not in working directory");
        }

        auto scores = Logic::HighScore::getInstance()->getScores();

        for (int i=0; i<scores.size(); i++){

            std::unique_ptr<sf::Text> score = std::make_unique<sf::Text>();
            score->setString(std::to_string(i+1)+". "+std::to_string(scores[i]));
            score->setFont(font);
            score->setCharacterSize(50);
            score->setFillColor(sf::Color{230, 230, 0});
            auto p = Camera::getInstance()->toPixels(Logic::Vector2D{-0.2, -0.3+0.1*i}, Logic::Vector2D<>{0, 0});

            score->setPosition((float) p.first[0], (float) p.first[1]);

            RenderWindowSingleton::getInstance()->drawBufferless(std::move(score));
        }
    }

    Scoreboard::Scoreboard(): UIObject{Logic::Vector2D<>{0, 0}, Logic::Vector2D<>{0, 0}} {

    }
} // View