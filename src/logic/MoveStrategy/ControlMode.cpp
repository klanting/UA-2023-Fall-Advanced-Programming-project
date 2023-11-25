//
// Created by tibov on 25/11/23.
//

#include "ControlMode.h"

namespace Logic {
    namespace Move {
        Vector2D ControlMode::getDirection(const Vector2D &to_pacman, const std::vector<Vector2D> &options) const {
            //options is a vector of every direction given by the controller

            Vector2D result{0, 0};
            std::for_each(options.begin(), options.end(), [&result](Vector2D d){result += d;});

            return result;
        }
    } // Logic
} // Move