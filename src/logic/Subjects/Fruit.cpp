//
// Created by tibov on 25/11/23.
//

#include "Fruit.h"

namespace Logic {
    Fruit::Fruit(const Vector2D &position, std::shared_ptr<Move::ModeManager> move_manager) : Collectable(position, Vector2D{0.1,0.1}, move_manager) {

    }
} // Logic