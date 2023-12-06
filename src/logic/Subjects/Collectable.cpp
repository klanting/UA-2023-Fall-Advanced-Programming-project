//
// Created by tibov on 25/11/23.
//

#include "Collectable.h"

namespace Logic {
    Collectable::Collectable(const Vector2D &position, const Vector2D& size,  std::shared_ptr<Move::ModeManager> move_manager) : EntityModel(position, size, 0, move_manager) {
        consumable = true;
    }

    Collectable::~Collectable() {

    }

    bool Collectable::handleDead(std::vector<std::shared_ptr<Subject>> others) {
        return true;
    }

} // Logic