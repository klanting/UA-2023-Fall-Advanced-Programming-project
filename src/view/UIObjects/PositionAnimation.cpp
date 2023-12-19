//
// Created by tibov on 19/12/23.
//

#include "PositionAnimation.h"

namespace View {
    PositionAnimation::PositionAnimation(const Logic::Vector2D &position, const Logic::Vector2D &size, double delay,
                                         std::vector<std::unique_ptr<Image>> images, double left_bound,
                                         double right_bound): Animation{position, size, delay, std::move(images)}, left_bound{left_bound}, right_bound{right_bound} {

    }

    void PositionAnimation::render() const {

    }
} // View