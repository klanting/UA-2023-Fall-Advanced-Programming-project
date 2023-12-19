//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_CONTROLMODE_H
#define PROJECTPACMAN_CONTROLMODE_H
#include "Mode.h"

#include "../Controller/Controller.h"
#include <algorithm>
#include "../Controller/MovementController.h"
namespace Logic {
    namespace Move {

        /**
         * This Mode will depend his Direction on a Controller
         * */
        class ControlMode: public Mode{
        public:
            ControlMode() =default;
            void makeDirection(const Vector2D& to_pacman, const std::vector<Vector2D>& options) override;

            const Vector2D &getDirection() const override;
        private:

        };

    } // Logic
} // Move

#endif //PROJECTPACMAN_CONTROLMODE_H
