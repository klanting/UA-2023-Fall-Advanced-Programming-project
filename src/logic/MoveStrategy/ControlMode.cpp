
#include "ControlMode.h"

    namespace Logic::Move {
        void ControlMode::makeDirection(const Vector2D<> &to_pacman, const std::vector<Vector2D<>> &options){
        }

        const Vector2D<> &ControlMode::getDirection() const {
            //give the direction given by the controller
            return Controller::Controller::getInstance()->getDataVector();
        }

    } // Logic
// Move