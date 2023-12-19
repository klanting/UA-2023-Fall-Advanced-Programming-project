//
// Created by tibov on 19/12/23.
//

#include "ImageAnimation.h"

namespace View {
    ImageAnimation::ImageAnimation(const Logic::Vector2D &position, const Logic::Vector2D &size, double delay,
                                   const std::vector<Image> &images): Animation{position, size, delay}, images{images} {

    }

    void ImageAnimation::render() const {


    }
} // View