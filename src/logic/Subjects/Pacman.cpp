//
// Created by tibov on 25/11/23.
//

#include "Pacman.h"
#include "../MoveStrategy/ControlMode.h"
namespace Logic {
    Pacman::Pacman(const Vector2D<> &position, const std::shared_ptr<Move::ModeManager>& move_manager) : EntityModel(position, Vector2D{0.13,0.13}, 0.5, move_manager) {

    }

    bool Pacman::handleDead(const std::vector<std::shared_ptr<EntityModel>>& others) {
        for (const auto& other: others){
            other->goStartPosition();
        }

        return false;
    }
} // Logic