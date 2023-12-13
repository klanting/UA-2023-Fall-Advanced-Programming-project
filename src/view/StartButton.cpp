//
// Created by tibov on 13/12/23.
//

#include "StartButton.h"
#include "Camera.h"

namespace View {
    StartButton::StartButton(const Logic::Vector2D &position, const Logic::Vector2D &size): Button{position, size} {
        texture.loadFromFile("sprites/pacman_menu.png", sf::IntRect(0, 0, 300, 500));
    }

    void StartButton::render() const{
        std::unique_ptr<sf::Sprite> button_print = std::make_unique<sf::Sprite>();
        button_print->setTexture(texture);

        button_print->setTextureRect(sf::IntRect(1, 439, 300, 60));

        auto p = Camera::getInstance()->toPixels(position, Logic::Vector2D{0, 0});
        button_print->setPosition(p.first[0], p.first[1]);
        button_print->setScale(RenderWindowSingleton::getInstance()->getSize().x / 300.0, RenderWindowSingleton::getInstance()->getSize().y / 300.0);

        RenderWindowSingleton::getInstance()->draw_bufferless(std::move(button_print));

        auto data = Camera::getInstance()->toPixels(position, size);


    }

    StartButton::StartButton():Button{} {

    }
} // View