//
// Created by tibov on 19/12/23.
//

#include "Image.h"
#include <iostream>
namespace View {
    void Image::render() const {
        RenderWindowSingleton::getInstance()->draw_bufferless(sprite);

        /*
        auto data = Camera::getInstance()->toPixels(position, size);

        std::vector<sf::Vertex> vertices;
        sf::Color color = sf::Color::Blue;

        vertices.push_back(sf::Vertex{sf::Vector2f(data.first[0], data.first[1]), color});
        vertices.push_back(sf::Vertex{sf::Vector2f((data.first)[0], (data.first+data.second)[1]), color});
        vertices.push_back(sf::Vertex{sf::Vector2f((data.first+data.second)[0], (data.first+data.second)[1]), color});
        vertices.push_back(sf::Vertex{sf::Vector2f((data.first+data.second)[0], (data.first)[1]), color});
        vertices.push_back(sf::Vertex{sf::Vector2f(data.first[0], data.first[1]), color});

        std::shared_ptr<sf::VertexArray> square = std::make_shared<sf::VertexArray>(sf::LineStrip);
        for (auto& v: vertices){
            square->append(v);
        }

        RenderWindowSingleton::getInstance()->draw_bufferless(square);
        */

    }

    Image::Image(const Logic::Vector2D &position, const Logic::Vector2D &size, const Logic::Vector2D &pixel_size,
                 const std::shared_ptr<sf::Sprite>& sprite, const sf::Texture& texture): UIObject{position, size}, pixel_size{pixel_size}, sprite{sprite}, texture{texture} {
        auto p = Camera::getInstance()->toPixels(position, size);
        Image::sprite->setPosition(p.first[0], p.first[1]);
        Image::sprite->setScale(p.second[0] / pixel_size[0], p.second[1]  / pixel_size[1]);

        Image::sprite->setTexture(Image::texture);


    }

    void Image::setPosition(const Logic::Vector2D &position) {
        Image::position = position;
        auto p = Camera::getInstance()->toPixels(Image::position, size);
        sprite->setPosition(p.first[0], p.first[1]);

    }

    Logic::Vector2D Image::getPosition() {
        return Logic::Vector2D{sprite->getPosition().x, sprite->getPosition().y};
    }

    void Image::cutOff(double pct) const {
        sf::IntRect original_rect = sprite->getTextureRect();

        auto data = Camera::getInstance()->toPixels(position, size);

        int pixel_change = (int)(pct*data.second[0]);
        original_rect.left = 1+(int)(pct*pixel_size[0]);



        sprite->setPosition(data.first[0]+pixel_change, data.first[1]);
        sprite->setTextureRect(original_rect);

    }
} // View