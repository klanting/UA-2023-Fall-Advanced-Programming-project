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

        /**
         * this mode decides which direction an entity goes to
         * */
        class Mode {
        public:
            Mode();
            virtual void makeDirection(const Vector2D<>& to_entity, const std::vector<Vector2D<>>& options) = 0;

            virtual const Vector2D<> &getDirection() const;

        protected:
            Vector2D<> findBest(const Vector2D<>& to_entity, const std::vector<Vector2D<>>& options, const std::function<bool(double, double)>& op) const;
            Vector2D<> takeRandom(const std::vector<Vector2D<>>& options) const;
            Vector2D<> direction;
        private:

        };

    } // Logic
} // Move

#endif //PROJECTPACMAN_MODE_H
