//
// Created by tibov on 19/12/23.
//

#include "Animation.h"

namespace View {
    Animation::Animation(const Logic::Vector2D &position, const Logic::Vector2D &size, double delay, std::vector<std::unique_ptr<Image>> images): UIObject{position, size} {
        for (int i=0; i<images.size(); i++){
            Animation::images.push_back(std::move(images[i]));
        }

        animation_delay = delay;
        total_delay = delay;

    }

} // View