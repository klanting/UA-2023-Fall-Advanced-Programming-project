//
// Created by tibov on 25/11/23.
//

#include "ModeManager.h"

namespace Logic {
    namespace Move {
        ModeManager::ModeManager(std::unique_ptr<Mode> mode){
            strategy = std::unique_ptr<Mode>(std::move(mode));
        }

        Vector2D ModeManager::getDirection(const Vector2D &to_pacman, const std::vector<Vector2D> &options) const {
            return strategy->getDirection(to_pacman, options);
        }

        void ModeManager::setStrategy(std::unique_ptr<Mode> mode) {
            ModeManager::strategy = std::unique_ptr<Mode>(std::move(mode));
        }
    } // Logic
} // Move