//
// Created by tibov on 30/11/23.
//

#include "CoinView.h"
#include <iostream>
namespace View {

    CoinView::CoinView(std::weak_ptr<Logic::EntityModel> entity) : EntityView(entity) {
        texture.loadFromFile("sprites/Sprites.png", sf::IntRect(400+10, 452+10, 40, 600));
        //sprite.setTexture(texture);

        pixel_width = 20;
        pixel_height = 20;

    }

    int CoinView::getTop() {
        return 0;
    }
} // View

