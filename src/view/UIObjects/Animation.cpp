//
// Created by tibov on 19/12/23.
//

#include "Animation.h"

namespace View {
    Animation::Animation(double delay, std::vector<std::unique_ptr<Image>> images): UIObject{Logic::Vector2D{0, 0}, Logic::Vector2D{0, 0}} {
        for (int i=0; i<images.size(); i++){
            Animation::images.push_back(std::move(images[i]));
        }

        animation_delay = delay;
        total_delay = delay;

    }

} // View