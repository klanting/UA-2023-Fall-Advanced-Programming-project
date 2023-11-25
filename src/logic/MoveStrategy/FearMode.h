//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_FEARMODE_H
#define PROJECTPACMAN_FEARMODE_H
#include "Mode.h"
namespace Logic {
    namespace Move {

        class FearMode: public Mode{
        public:
            FearMode() =default;
            Vector2D getDirection(const Vector2D& to_pacman, const std::vector<Vector2D>& options) const override;
        private:

        };

    } // Logic
} // Move

#endif //PROJECTPACMAN_FEARMODE_H
