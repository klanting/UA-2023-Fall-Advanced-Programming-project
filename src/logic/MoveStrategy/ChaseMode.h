//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_CHASEMODE_H
#define PROJECTPACMAN_CHASEMODE_H
#include "Mode.h"
namespace Logic {
    namespace Move {

        class ChaseMode: public Mode{
        public:
            ChaseMode() = default;
            void makeDirection(const Vector2D& to_pacman, const std::vector<Vector2D>& options) override;
        private:

        };

    } // Logic
} // Move

#endif //PROJECTPACMAN_CHASEMODE_H
