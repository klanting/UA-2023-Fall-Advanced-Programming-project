//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_CONTROLMODE_H
#define PROJECTPACMAN_CONTROLMODE_H
#include "Mode.h"
#include "../Controller/ControllerObserver.h"
#include "../Controller/Controller.h"
#include <algorithm>
namespace Logic {
    namespace Move {

        class ControlMode: public Mode, Controller::ControllerObserver{
        public:
            ControlMode() =default;
            void makeDirection(const Vector2D& to_pacman, const std::vector<Vector2D>& options) override;
            void update(std::weak_ptr<Controller::Controller> input_controller) override;
        private:

        };

    } // Logic
} // Move

#endif //PROJECTPACMAN_CONTROLMODE_H
