//
// Created by tibov on 14/12/23.
//

#include "MenuButton.h"

namespace View {
    MenuButton::MenuButton(const Logic::Vector2D &position, const Logic::Vector2D &size): Button{position, size} {
        texture.loadFromFile("sprites/pacman_menu.png", sf::IntRect(0, 0, 300, 700));
        button_print = std::make_shared<sf::Sprite>();

        auto p = Camera::getInstance()->toPixels(position, size);
        button_print->setPosition(p.first[0], p.first[1]);
        button_print->setScale(RenderWindowSingleton::getInstance()->getSize().x / 300.0, RenderWindowSingleton::getInstance()->getSize().y / 300.0);

    }

    void MenuButton::render() const{

        button_print->setTexture(texture);
        button_print->setTextureRect(sf::IntRect(0, 488, 300, 48));


        RenderWindowSingleton::getInstance()->draw_bufferless(button_print);

    }

    MenuButton::MenuButton():Button{} {

    }
} // View