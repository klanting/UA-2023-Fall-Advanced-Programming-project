

#include "PacmanView.h"

namespace View {


    PacmanView::PacmanView(const std::weak_ptr<Logic::Pacman>& entity) : EntityView(entity) {
        texture.loadFromFile("sprites/Sprites.png", sf::IntRect(850, 2, 40, 600));
        //sprite.setTexture(texture);

    }

    int PacmanView::getTop() {
        if (entity.expired()){
            throw std::bad_weak_ptr();
        }

        auto e = entity.lock();

        int pixel_top = 0;

        checkAnimation();

        if (e->isUp()){
            pixel_top = 500;
        }

        if (e->isDown()){
            pixel_top = 200;
        }

        if (e->isLeft()){
            pixel_top = 350;
        }

        if (e->isRight()){
            pixel_top = 50;
        }

        if (pixel_top != 0){
            pixel_top += animation_index*50;
        }

        return pixel_top;

    }
} // View