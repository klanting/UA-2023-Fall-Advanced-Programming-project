//
// Created by tibov on 25/11/23.
//

#include "ControlMode.h"
#include <iostream>
namespace Logic {
    namespace Move {
        void ControlMode::makeDirection(const Vector2D &to_pacman, const std::vector<Vector2D> &options){
            //options is a vector of every direction given by the controller

            //Vector2D result{0, 0};
            //std::for_each(options.begin(), options.end(), [&result](Vector2D d){result += d;});

            direction = Controller::MovementController::getInstance()->getDataVector();
        }

        const Vector2D &ControlMode::getDirection() const {
            return Controller::MovementController::getInstance()->getDataVector();
        }

    } // Logic
} // Move