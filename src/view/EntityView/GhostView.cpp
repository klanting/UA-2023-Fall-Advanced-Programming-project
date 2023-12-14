//
// Created by tibov on 30/11/23.
//

#include "GhostView.h"
#include <iostream>
namespace View {


    GhostView::GhostView(std::weak_ptr<Logic::Ghost> entity, int color_index) : EntityView(entity), color_index{color_index} {
        texture.loadFromFile("sprites/Sprites.png", sf::IntRect(0, 2, 40+50*6, 1000));

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

        if (entity.lock()->isConsumable()){
            pixel_top += 550;
        }
        return pixel_top;
    }

    int GhostView::getLeft() {
        int pixel_left = color_index*50;
        if (entity.lock()->isConsumable()){
            if (!entity.lock()->AlmostChase()){
                return 0;
            }

            return animation_index*50;

        }

        return pixel_left;
    }
} // View