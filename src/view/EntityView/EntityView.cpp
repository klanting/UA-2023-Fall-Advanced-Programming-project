//
// Created by tibov on 30/11/23.
//

#include "EntityView.h"
#include "../../logic/Subjects/Ghost.h"
#include "../../logic/Subjects/Coin.h"
#include "../../logic/Subjects/Fruit.h"
#include "../../logic/Subjects/Pacman.h"
#include "../../logic/Subjects/Wall.h"
#include "../../logic/Subjects/Intersection.h"
#include <iostream>
namespace View {
    template class EntityView<Logic::Ghost>;
    template class EntityView<Logic::Coin>;
    template class EntityView<Logic::Fruit>;
    template class EntityView<Logic::Pacman>;
    template class EntityView<Logic::Wall>;
    template class EntityView<Logic::Intersection>;

    template<typename T>
    EntityView<T>::EntityView(std::weak_ptr<T> entity): entity{entity}, animation_index{0}, animation_delay{0.25} {
        sprite = std::make_shared<sf::Sprite>();
        sprite->setTexture(texture);

    }

    template<typename T>
    void EntityView<T>::checkAnimation() {
        //run the animation delay and determine the animation index
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

    template<typename T>
    void EntityView<T>::moved() {
        typedef std::pair<Logic::Vector2D<>, Logic::Vector2D<>> PixelData;

        if (entity.expired()){
            throw std::bad_weak_ptr();
        }

        auto e = entity.lock();

        //determine the pixel based position and draw the sprite
        PixelData data = Camera::getInstance()->toPixels(e->getPosition(), e->getSize());

        sprite->setPosition((float) data.first[0], (float) data.first[1]);
        sprite->setScale(data.second[0]/(pixel_width-2), data.second[1]/(pixel_height-2));


        int pixel_top = getTop();

        sprite->setTextureRect(sf::IntRect(getLeft(), pixel_top, pixel_width, pixel_height));

        RenderWindowSingleton::getInstance()->draw(entity, sprite);


    }

    template<typename T>
    int EntityView<T>::getLeft() {
        return 0;
    }

    template<typename T>
    void EntityView<T>::consume(std::weak_ptr<Logic::EntityModel> other) {

    }

    template<typename T>
    void EntityView<T>::died() {

    }


} // View