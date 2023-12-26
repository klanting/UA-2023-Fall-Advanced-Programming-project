//
// Created by tibov on 30/11/23.
//

#include "WallView.h"
#include <iostream>
namespace View {


    void WallView::moved() {
        typedef std::pair<Logic::Vector2D<>, Logic::Vector2D<>> PixelData;


        if (entity.expired()){
            throw std::bad_weak_ptr();
        }

        auto e = entity.lock();
        PixelData data = Camera::getInstance()->toPixels(e->getPosition(), e->getSize());

        //draws rectangle representing a wall
        std::vector<sf::Vertex> vertices;
        sf::Color color = sf::Color::Blue;

        vertices.emplace_back(sf::Vector2f((float) data.first[0], (float) data.first[1]), color);
        vertices.emplace_back(sf::Vector2f((float) (data.first)[0], (float) (data.first+data.second)[1]), color);
        vertices.emplace_back(sf::Vector2f((float) (data.first+data.second)[0], (float) (data.first+data.second)[1]), color);
        vertices.emplace_back(sf::Vector2f((float) (data.first+data.second)[0], (float) (data.first)[1]), color);
        vertices.emplace_back(sf::Vector2f((float) data.first[0], (float) data.first[1]), color);

        std::shared_ptr<sf::VertexArray> square = std::make_shared<sf::VertexArray>(sf::LineStrip);
        for (auto& v: vertices){
            square->append(v);
        }

        RenderWindowSingleton::getInstance()->draw(entity, square);
    }

    WallView::WallView(const std::weak_ptr<Logic::Wall>& entity) : EntityView(entity) {

    }

    int WallView::getTop() {
        return 0;
    }
} // View