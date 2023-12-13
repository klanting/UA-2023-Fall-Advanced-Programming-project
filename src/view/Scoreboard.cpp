//
// Created by tibov on 12/12/23.
//

#include "Scoreboard.h"
#include <fstream>
#include <algorithm>
#include "Camera.h"
#include "../logic/Vector2D.h"
#include "RenderWindowSingleton.h"

namespace View {
    std::shared_ptr<Scoreboard> Scoreboard::getInstance() {
        if (!_instance){
            _instance = std::shared_ptr<Scoreboard>(new Scoreboard{});
        }
        return _instance;
    }

    Scoreboard::Scoreboard() {
        std::fstream score_file{"scoreboard"};

        std::string buffer;
        while (!score_file.eof()){
            char c = score_file.get();

            if (c == '\n'){
                if (!buffer.empty()){
                    scores.push_back(std::stoi(buffer));
                    buffer = "";
                }

            }else{
                buffer += c;
            }


        }
        score_file.close();
        if (!buffer.empty() && buffer != "\377"){
            scores.push_back(std::stoi(buffer));
        }


    }

    void Scoreboard::add(unsigned int score) {
        scores.push_back(score);

    }

    Scoreboard::~Scoreboard() {
        std::fstream score_file{"scoreboard"};
        std::sort(scores.begin(), scores.end(), std::greater<>());
        for (int i=0; i<5; i++){
            if (scores.size() <= i){
                break;
            }
            score_file << scores[i];
            score_file << '\n';
        }
        score_file.close();

    }

    void Scoreboard::render() {

        sf::Font font;
        font.loadFromFile("arial.ttf");

        for (int i=0; i<5; i++){
            if (scores.size() <= i){
                break;
            }
            std::unique_ptr<sf::Text> score = std::make_unique<sf::Text>();
            score->setString(std::to_string(i+1)+". "+std::to_string(scores[i]));
            score->setFont(font);
            score->setCharacterSize(50);
            score->setFillColor(sf::Color{230, 230, 0});
            auto p = Camera::getInstance()->toPixels(Logic::Vector2D{-0.2, -0.3+0.1*i}, Logic::Vector2D{0, 0});

            score->setPosition(p.first[0], p.first[1]);

            RenderWindowSingleton::getInstance()->draw_bufferless(std::move(score));
        }
    }
} // View