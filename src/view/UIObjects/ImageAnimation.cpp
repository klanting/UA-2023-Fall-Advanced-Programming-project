//
// Created by tibov on 19/12/23.
//

#include "ImageAnimation.h"
#include <iostream>
namespace View {
    ImageAnimation::ImageAnimation(double delay,
                                   std::vector<std::unique_ptr<Image>> images): Animation{Logic::Vector2D{0, 0}, Logic::Vector2D{0, 0}, delay, std::move(images)}{

    }

    void ImageAnimation::render() const {
        double d = Logic::Stopwatch::getInstance()->getDeltaTime();
        animation_delay -= d;
        while (animation_delay < 0){
            animation_index = (animation_index + 1) % (int) images.size();
            animation_delay += total_delay;
        }

        images[animation_index]->render();
    }

} // View