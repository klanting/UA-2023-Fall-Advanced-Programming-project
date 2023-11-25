//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_MODEMANAGER_H
#define PROJECTPACMAN_MODEMANAGER_H
#include "Mode.h"
#include "memory"
namespace Logic {
    namespace Move {

        class ModeManager {
        public:
            ModeManager(std::unique_ptr<Mode> mode);
            Vector2D getDirection(const Vector2D& to_pacman, const std::vector<Vector2D>& options) const;

            void setStrategy(std::unique_ptr<Mode> mode);

        private:
            std::unique_ptr<Mode> strategy;
        };

    } // Move
} //Logic

#endif //PROJECTPACMAN_MODEMANAGER_H
