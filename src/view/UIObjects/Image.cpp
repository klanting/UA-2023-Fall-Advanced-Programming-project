//
// Created by tibov on 19/12/23.
//

#include "Image.h"

namespace View {
    void Image::render() const {
        sprite->setTexture(texture);

        RenderWindowSingleton::getInstance()->draw_bufferless(sprite);
    }

    Image::Image(const Logic::Vector2D &position, const Logic::Vector2D &size, const Logic::Vector2D &pixel_size,
                 std::shared_ptr<sf::Sprite> sprite, const sf::Texture& texture): UIObject{position, size}, pixel_size{pixel_size}, sprite{sprite}, texture{texture} {
        auto p = Camera::getInstance()->toPixels(position, size);
        sprite->setPosition(p.first[0], p.first[1]);
        sprite->setScale(p.second[0] / pixel_size[0], p.second[1]  / pixel_size[1]);


    }
} // View