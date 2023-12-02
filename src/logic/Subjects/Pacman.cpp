//
// Created by tibov on 25/11/23.
//

#include "Pacman.h"
#include "../MoveStrategy/ControlMode.h"
namespace Logic {
    Pacman::Pacman(const Vector2D &position, std::shared_ptr<Move::ModeManager> move_manager) : EntityModel(position, 0.5, move_manager) {

    }
} // Logic