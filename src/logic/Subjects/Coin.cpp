//
// Created by tibov on 25/11/23.
//

#include "Coin.h"

namespace Logic {
    Coin::Coin(const Vector2D &position, std::shared_ptr<Move::ModeManager> move_manager) : Collectable(position, move_manager) {

    }
} // Logic