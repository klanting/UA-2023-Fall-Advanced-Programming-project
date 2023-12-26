//
// Created by tibov on 30/11/23.
//

#include "WallView.h"
#include <iostream>
namespace View {


    void WallView::moved() {
        typedef std::pair<Logic::Vector2D<>, Logic::Vector2D<>> PixelData;


        if (entity.expired()){
            throw "entity doesnt exist";
        }

        auto e = entity.lock();
        PixelData data = Camera::getInstance()->toPixels(e->getPosition(), e->getSize());


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

        RenderWindowSingleton::getInstance()->draw(entity, square);
    }

    WallView::WallView(std::weak_ptr<Logic::Wall> entity) : EntityView(entity) {

    }

    int WallView::getTop() {
        return 0;
    }
} // View