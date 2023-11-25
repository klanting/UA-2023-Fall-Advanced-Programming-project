//
// Created by tibov on 25/11/23.
//

#include "Pacman.h"
#include "../MoveStrategy/ControlMode.h"
namespace Logic {
    Pacman::Pacman(const Vector2D &position) : EntityModel(position, std::make_unique<Move::ControlMode>()) {

    }
} // Logic