//
// Created by tibov on 25/11/23.
//

#include "Wall.h"

namespace Logic {
    Wall::Wall(const Vector2D &position, std::shared_ptr<Move::ModeManager> move_manager) : EntityModel(position, Vector2D{0.1,0.1}, 0, move_manager) {

    }

    void Wall::handleImpassable(std::vector<std::weak_ptr<Subject>> others, bool fix) {

    }
} // Logic