//
// Created by tibov on 13/12/23.
//

#include "Button.h"
#include "Camera.h"
namespace View {
    Button::Button(const Logic::Vector2D &position, const Logic::Vector2D &size): position{position}, size{size} {
    }

    bool Button::isClicked(const Logic::Vector2D &click_position) {

        auto p = Camera::getInstance()->toPixels(position, size);

        bool x = p.first[0] < click_position[0] && click_position[0] < (p.first+p.second)[0];
        bool y = p.first[1] < click_position[1] && click_position[1] < (p.first+p.second)[1];

        return x && y;
    }

    Button::Button():position{Logic::Vector2D{0,0}}, size{Logic::Vector2D{0,0}} {

    }

} // View