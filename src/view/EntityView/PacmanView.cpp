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
        sprite.setScale(data.second[0]/50, data.second[1]/50);
        sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));

        RenderWindowSingleton::getInstance()->getWindow()->draw(sprite);

    }

    PacmanView::PacmanView(std::weak_ptr<Logic::EntityModel> entity) : EntityView(entity) {
        texture.loadFromFile("sprites/Sprites.png", sf::IntRect(850, 0, 50, 50));
        sprite.setTexture(texture);

    }
} // View