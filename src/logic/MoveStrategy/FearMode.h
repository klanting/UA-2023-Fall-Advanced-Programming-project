//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_FEARMODE_H
#define PROJECTPACMAN_FEARMODE_H
#include "Mode.h"
namespace Logic {
    namespace Move {

        /**
         * Chase Mode will decide its direction by the following steps
         * 50% chance it takes a random direction (within possible options)
         * 50% chance it want to maximize the Manhattan distance with a give Entity Direction in my project: Direction to Pacman
         * */
        class FearMode: public Mode{
        public:
            FearMode() =default;
            void makeDirection(const Vector2D<>& to_entity, const std::vector<Vector2D<>>& options) override;
        private:

        };

    } // Logic
} // Move

#endif //PROJECTPACMAN_FEARMODE_H
