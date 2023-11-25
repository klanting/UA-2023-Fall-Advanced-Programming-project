//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_MODE_H
#define PROJECTPACMAN_MODE_H
#include "../Vector2D.h"
#include <vector>
namespace Logic {
    namespace Move {

        class Mode {
        public:
            Mode() = default;
            virtual Vector2D getDirection(Vector2D& to_pacman, const std::vector<Vector2D>& options) const = 0;
        private:
        };

    } // Logic
} // Move

#endif //PROJECTPACMAN_MODE_H
