//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_MODE_H
#define PROJECTPACMAN_MODE_H
#include "../Vector2D.h"
#include <vector>
#include <functional>
#include "../Random.h"
#include <algorithm>

namespace Logic {
    namespace Move {

        class Mode {
        public:
            Mode() = default;
            virtual Vector2D getDirection(const Vector2D& to_pacman, const std::vector<Vector2D>& options) const = 0;
        protected:
            Vector2D findBest(const Vector2D& to_pacman, const std::vector<Vector2D>& options, const std::function<bool(double, double)>& op) const;
            Vector2D takeRandom(const std::vector<Vector2D>& options) const;

        private:
        };

    } // Logic
} // Move

#endif //PROJECTPACMAN_MODE_H
