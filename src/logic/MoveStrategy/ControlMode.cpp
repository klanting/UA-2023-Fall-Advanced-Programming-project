//
// Created by tibov on 25/11/23.
//

#include "ControlMode.h"
#include <iostream>
namespace Logic {
    namespace Move {
        void ControlMode::makeDirection(const Vector2D<> &to_pacman, const std::vector<Vector2D<>> &options){
        }

        const Vector2D<> &ControlMode::getDirection() const {
            //give the direction given by the controller
            return Controller::MovementController::getInstance()->getDataVector();
        }

    } // Logic
} // Move