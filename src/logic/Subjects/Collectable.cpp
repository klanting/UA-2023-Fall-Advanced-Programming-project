//
// Created by tibov on 25/11/23.
//

#include "Collectable.h"

namespace Logic {
    Collectable::Collectable(const Vector2D &position, std::shared_ptr<Move::ModeManager> move_manager) : EntityModel(position, 0, move_manager) {

    }
} // Logic