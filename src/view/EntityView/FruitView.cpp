//
// Created by tibov on 30/11/23.
//

#include "FruitView.h"

namespace View {



    FruitView::FruitView(const std::weak_ptr<Logic::Fruit>& entity) : EntityView(entity) {
        texture.loadFromFile("sprites/Sprites.png", sf::IntRect(400+10, 452+10, 40, 600));
        //sprite.setTexture(texture);

        pixel_width = 20;
        pixel_height = 20;
    }

    int FruitView::getTop() {
        return 0;
    }
} // View