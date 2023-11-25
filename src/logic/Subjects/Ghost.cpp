//
// Created by tibov on 25/11/23.
//

#include "Ghost.h"
#include "../MoveStrategy/ChaseMode.h"
namespace Logic {
    Ghost::Ghost(const Vector2D &position) : EntityModel(position, std::make_unique<Move::ChaseMode>()) {

    }
} // Logic