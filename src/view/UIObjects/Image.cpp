//
// Created by tibov on 19/12/23.
//

#include "Image.h"
#include <iostream>
namespace View {
    void Image::render() const {
        RenderWindowSingleton::getInstance()->draw_bufferless(sprite);

    }

    Image::Image(const Logic::Vector2D &position, const Logic::Vector2D &size, const Logic::Vector2D &pixel_size,
                 const std::shared_ptr<sf::Sprite>& sprite, const sf::Texture& texture): UIObject{position, size}, pixel_size{pixel_size}, sprite{sprite}, texture{texture} {
        auto p = Camera::getInstance()->toPixels(position, size);
        Image::sprite->setPosition(p.first[0], p.first[1]);
        Image::sprite->setScale(p.second[0] / pixel_size[0], p.second[1]  / pixel_size[1]);

        Image::sprite->setTexture(Image::texture);


    }
} // View