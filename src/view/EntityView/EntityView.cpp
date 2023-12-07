//
// Created by tibov on 30/11/23.
//

#include "EntityView.h"
#include "../../logic/Stopwatch.h"
#include <iostream>
namespace View {
    EntityView::EntityView(std::weak_ptr<Logic::EntityModel> entity): entity{entity}, animation_index{0}, animation_delay{0.25} {

    }

    void EntityView::checkAnimation() {
        int last_tick = Logic::Stopwatch::getInstance()->getTickIteration();
        if (last_tick_iteration == last_tick){
            return;
        }
        last_tick_iteration = last_tick;

        double d = Logic::Stopwatch::getInstance()->getDeltaTime();
        animation_delay -= d;
        while (animation_delay < 0){
            animation_index = (animation_index + 1) % 2;
            animation_delay += 0.25;
        }

    }

    void EntityView::moved() {
        typedef std::pair<Logic::Vector2D, Logic::Vector2D> PixelData;

        if (entity.expired()){
            throw "entity doesnt exist";
        }

        auto e = entity.lock();

        PixelData data = Camera::getInstance()->toPixels(e->getPosition(), e->getSize());

        std::unique_ptr<sf::Sprite> sprite = std::make_unique<sf::Sprite>();
        sprite->setTexture(texture);
        sprite->setPosition(data.first[0], data.first[1]);
        sprite->setScale(data.second[0]/(pixel_width-2), data.second[1]/(pixel_height-2));


        int pixel_top = getTop();

        sprite->setTextureRect(sf::IntRect(getLeft(), pixel_top, pixel_width, pixel_height));

        RenderWindowSingleton::getInstance()->draw(entity, std::move(sprite));

    }

    int EntityView::getLeft() {
        return 0;
    }

    void EntityView::consume(std::weak_ptr<Logic::Subject> other) {

    }

    void EntityView::died() {

    }

} // View