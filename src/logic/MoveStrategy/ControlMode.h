//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_CONTROLMODE_H
#define PROJECTPACMAN_CONTROLMODE_H
#include "Mode.h"
#include <algorithm>
namespace Logic {
    namespace Move {

        class ControlMode: public Mode{
        public:
            ControlMode() =default;
            void makeDirection(const Vector2D& to_pacman, const std::vector<Vector2D>& options) override;
        private:

        };

    } // Logic
} // Move

#endif //PROJECTPACMAN_CONTROLMODE_H
