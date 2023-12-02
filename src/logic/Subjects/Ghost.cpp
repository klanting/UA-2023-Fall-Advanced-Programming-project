//
// Created by tibov on 25/11/23.
//

#include "Ghost.h"
#include "../MoveStrategy/ChaseMode.h"
namespace Logic {
    Ghost::Ghost(const Vector2D &position, std::shared_ptr<Move::ModeManager> move_manager) : EntityModel(position, 1,move_manager) {

    }
} // Logic