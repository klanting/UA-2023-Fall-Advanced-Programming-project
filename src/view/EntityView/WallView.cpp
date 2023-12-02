//
// Created by tibov on 30/11/23.
//

#include "WallView.h"

namespace View {


    void WallView::moved() {
        typedef std::pair<Logic::Vector2D, Logic::Vector2D> PixelData;


        if (entity.expired()){
            throw "entity doesnt exist";
        }

        auto e = entity.lock();
        PixelData data = Camera::getInstance()->toPixels(e->getPosition(), e->getSize());


        RenderWindowSingleton::getInstance()->getWindow()->draw(sprite);
    }

    WallView::WallView(std::weak_ptr<Logic::EntityModel> entity) : EntityView(entity) {

    }
} // View