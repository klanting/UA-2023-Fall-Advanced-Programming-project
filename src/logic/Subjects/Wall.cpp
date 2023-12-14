//
// Created by tibov on 25/11/23.
//

#include "Wall.h"

namespace Logic {
    Wall::Wall(const Vector2D &position, const Vector2D &size, std::shared_ptr<Move::ModeManager> move_manager) : EntityModel(position, size, 0, move_manager) {

    }

    void Wall::handleInpassable(std::weak_ptr<EntityModel> other, bool fix) {

    }
} // Logic