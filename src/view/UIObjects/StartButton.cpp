//
// Created by tibov on 13/12/23.
//

#include "StartButton.h"


namespace View {
    StartButton::StartButton(const Logic::Vector2D<> &position, const Logic::Vector2D<> &size): ImageButton{position, size} {
        sf::Texture texture;
        texture.loadFromFile("sprites/pacman_menu.png", sf::IntRect(0, 0, 300, 500));
        std::shared_ptr<sf::Sprite> button_print = std::make_shared<sf::Sprite>();
        button_print->setTextureRect(sf::IntRect(1, 439, 136, 48));
        image = std::make_unique<Image>(position, size, Logic::Vector2D<>{136, 48}, button_print, texture);


    }



    StartButton::StartButton():ImageButton{} {

    }
} // View