//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_PASSIVEMODE_H
#define PROJECTPACMAN_PASSIVEMODE_H
#include "Mode.h"
namespace Logic {
    namespace Move {

        class PassiveMode: public Mode{
            PassiveMode() = default;
            Vector2D getDirection(const Vector2D& to_pacman, const std::vector<Vector2D>& options) const override;
        };

    } // Logic
} // Move

#endif //PROJECTPACMAN_PASSIVEMODE_H
