//
// Created by tibov on 14/12/23.
//

#include "MenuButton.h"

namespace View {
    MenuButton::MenuButton(const Logic::Vector2D<> &position, const Logic::Vector2D<> &size): Button{position, size} {

        sf::Texture texture;
        texture.loadFromFile("sprites/pacman_menu.png", sf::IntRect(0, 0, 300, 700));
        std::shared_ptr<sf::Sprite> button_print = std::make_shared<sf::Sprite>();
        button_print->setTextureRect(sf::IntRect(0, 488, 300, 48));
        image = std::make_shared<Image>(position, size, Logic::Vector2D<>{52, 48}, button_print, texture);

    }

    void MenuButton::render() const{
        image->render();

    }

    MenuButton::MenuButton():Button{} {

    }
} // View