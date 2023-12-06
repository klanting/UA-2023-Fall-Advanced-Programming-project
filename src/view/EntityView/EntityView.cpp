//
// Created by tibov on 30/11/23.
//

#include "EntityView.h"
#include "../../logic/Stopwatch.h"
#include <iostream>
namespace View {
    EntityView::EntityView(std::weak_ptr<Logic::EntityModel> entity): entity{entity}, animation_index{0}, animation_delay{0.25} {

    }

    void EntityView::checkAnimation() {
        double d = Logic::Stopwatch::getInstance()->getDeltaTime();
        animation_delay -= d;
        while (animation_delay < 0){
            animation_index = (animation_index + 1) % 2;
            animation_delay += 0.25;
        }

    }

    void EntityView::moved() {
        typedef std::pair<Logic::Vector2D, Logic::Vector2D> PixelData;

        if (entity.expired()){
            throw "entity doesnt exist";
        }

        auto e = entity.lock();

        PixelData data = Camera::getInstance()->toPixels(e->getPosition(), e->getSize());

        sprite.setPosition(data.first[0], data.first[1]);

        sprite.setScale(data.second[0]/(pixel_width-2), data.second[1]/(pixel_height-2));


        int pixel_top = getTop();

        sprite.setTextureRect(sf::IntRect(0, pixel_top, pixel_width, pixel_height));

        RenderWindowSingleton::getInstance()->getWindow()->draw(sprite);

        //debug reasons
        std::vector<sf::Vertex> vertices;
        vertices.push_back(sf::Vertex{sf::Vector2f(data.first[0], data.first[1]), sf::Color::Red});
        vertices.push_back(sf::Vertex{sf::Vector2f((data.first)[0], (data.first+data.second)[1]), sf::Color::Red});
        vertices.push_back(sf::Vertex{sf::Vector2f((data.first+data.second)[0], (data.first+data.second)[1]), sf::Color::Red});
        vertices.push_back(sf::Vertex{sf::Vector2f((data.first+data.second)[0], (data.first)[1]), sf::Color::Red});
        vertices.push_back(sf::Vertex{sf::Vector2f(data.first[0], data.first[1]), sf::Color::Red});
        RenderWindowSingleton::getInstance()->getWindow()->draw(&vertices[0], vertices.size(), sf::LineStrip);

    }

} // View