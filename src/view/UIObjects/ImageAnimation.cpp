//
// Created by tibov on 19/12/23.
//

#include "ImageAnimation.h"
#include <iostream>
namespace View {
    ImageAnimation::ImageAnimation(const Logic::Vector2D &position, const Logic::Vector2D &size, double delay,
                                   std::vector<std::unique_ptr<Image>> images): Animation{position, size, delay, std::move(images)}{
        for (int i=0; i<images.size(); i++){
            ImageAnimation::images.push_back(std::move(images[i]));
        }

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