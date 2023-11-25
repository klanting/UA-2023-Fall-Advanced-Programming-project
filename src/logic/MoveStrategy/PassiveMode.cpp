//
// Created by tibov on 25/11/23.
//

#include "PassiveMode.h"

namespace Logic {
    namespace Move {
        Vector2D PassiveMode::getDirection(const Vector2D &to_pacman, const std::vector<Vector2D> &options) const {
            //returns the 0 vector
            return Vector2D{0, 0};
        }
    } // Logic
} // Move