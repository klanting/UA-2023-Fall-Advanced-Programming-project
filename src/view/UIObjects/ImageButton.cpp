//
// Created by tibov on 28/12/23.
//

#include "ImageButton.h"

namespace View {
    ImageButton::ImageButton(const Logic::Vector2D<> &position, const Logic::Vector2D<> &size): Button{position, size} {

    }

    void ImageButton::render() const {
        if (image){
            image->render();
        }

    }

    ImageButton::ImageButton(const Logic::Vector2D<> &position, const Logic::Vector2D<> &size,
                             std::unique_ptr<Image> &&image): Button{position, size}, image{std::move(image)} {

    }
} // View