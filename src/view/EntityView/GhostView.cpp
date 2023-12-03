//
// Created by tibov on 30/11/23.
//

#include "GhostView.h"

namespace View {




    GhostView::GhostView(std::weak_ptr<Logic::EntityModel> entity, int color_index) : EntityView(entity) {
        texture.loadFromFile("sprites/Sprites.png", sf::IntRect(color_index*50, 2, 40, 600));
        sprite.setTexture(texture);

    }

    int GhostView::getTop() {
        if (entity.expired()){
            throw "entity doesnt exist";
        }

        auto e = entity.lock();

        int pixel_top = 0;

        checkAnimation();

        if (e->isUp()){
            pixel_top = 300;
        }

        if (e->isDown()){
            pixel_top = 100;
        }

        if (e->isLeft()){
            pixel_top = 200;
        }

        if (e->isRight()){
            pixel_top = 0;
        }

        pixel_top += animation_index*50;

        return pixel_top;
    }
} // View