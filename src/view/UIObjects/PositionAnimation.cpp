//
// Created by tibov on 22/12/23.
//

#include "PositionAnimation.h"

namespace View {
    void PositionAnimation::render() const {
        double d = Logic::Stopwatch::getInstance()->getDeltaTime();
        animation_delay -= d;
        while (animation_delay < 0){
            animation_delay += total_delay;
            animation_position += 0.037*animation_direction;
            if (animation_position >= 1 || animation_position <= 0){
                animation_direction *= -1;
            }
        }

        Logic::Vector2D resulting_position = start_position*(1-animation_position)+end_position*animation_position;
        for (auto& m: images){
            m->setPosition(resulting_position);
            m->render();
        }

    }

    PositionAnimation::PositionAnimation(double delay, std::vector<std::unique_ptr<Image>> images, const Logic::Vector2D &from,
                                         const Logic::Vector2D &to): Animation{Logic::Vector2D{0, 0}, Logic::Vector2D{0, 0}, delay, std::move(images)},
                                                                     start_position{from}, end_position{to} {

    }
} // View