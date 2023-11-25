//
// Created by tibov on 25/11/23.
//

#include "PassiveMode.h"

namespace Logic {
    namespace Move {
        void PassiveMode::makeDirection(const Vector2D &to_pacman, const std::vector<Vector2D> &options){
            //returns the 0 vector
            direction =  Vector2D{0, 0};
        }
    } // Logic
} // Move