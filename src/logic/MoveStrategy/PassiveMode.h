//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_PASSIVEMODE_H
#define PROJECTPACMAN_PASSIVEMODE_H
#include "Mode.h"
namespace Logic {
    namespace Move {

        class PassiveMode: public Mode{
        public:
            PassiveMode() = default;
            void makeDirection(const Vector2D& to_pacman, const std::vector<Vector2D>& options) override;
        private:
        };

    } // Logic
} // Move

#endif //PROJECTPACMAN_PASSIVEMODE_H
