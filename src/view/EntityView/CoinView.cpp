//
// Created by tibov on 30/11/23.
//

#include "CoinView.h"
#include <iostream>
namespace View {

    CoinView::CoinView(std::weak_ptr<Logic::EntityModel> entity) : EntityView(entity) {
        texture.loadFromFile("sprites/Sprites.png", sf::IntRect(400, 452, 40, 600));
        sprite.setTexture(texture);

    }

    int CoinView::getTop() {
        return 0;
    }
} // View

