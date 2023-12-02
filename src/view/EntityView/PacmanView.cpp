//
// Created by tibov on 30/11/23.
//

#include "PacmanView.h"
#include <iostream>
namespace View {


    void PacmanView::moved() {
        typedef std::pair<Logic::Vector2D, Logic::Vector2D> PixelData;

        if (entity.expired()){
            throw "entity doesnt exist";
        }

        auto e = entity.lock();
        PixelData data = Camera::getInstance()->toPixels(e->getPosition(), e->getSize());

        sprite.setPosition(data.first[0], data.first[1]);

        int pixel_width = 40;
        int pixel_height = 40;

        sprite.setScale(data.second[0]/pixel_width, data.second[1]/pixel_height);
        sprite.setTextureRect(sf::IntRect(0, 0, pixel_width, pixel_height));

        RenderWindowSingleton::getInstance()->getWindow()->draw(sprite);

        std::vector<sf::Vertex> vertices;
        vertices.push_back(sf::Vertex{sf::Vector2f(data.first[0], data.first[1]), sf::Color::Red});
        vertices.push_back(sf::Vertex{sf::Vector2f((data.first)[0], (data.first+data.second)[1]), sf::Color::Red});
        vertices.push_back(sf::Vertex{sf::Vector2f((data.first+data.second)[0], (data.first+data.second)[1]), sf::Color::Red});
        vertices.push_back(sf::Vertex{sf::Vector2f((data.first+data.second)[0], (data.first)[1]), sf::Color::Red});
        vertices.push_back(sf::Vertex{sf::Vector2f(data.first[0], data.first[1]), sf::Color::Red});
        RenderWindowSingleton::getInstance()->getWindow()->draw(&vertices[0], vertices.size(), sf::LineStrip);

    }

    PacmanView::PacmanView(std::weak_ptr<Logic::EntityModel> entity) : EntityView(entity) {
        texture.loadFromFile("sprites/Sprites.png", sf::IntRect(850, 0, 50, 50));
        sprite.setTexture(texture);

    }
} // View