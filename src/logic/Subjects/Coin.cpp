//
// Created by tibov on 25/11/23.
//

#include "Coin.h"

namespace Logic {
    Coin::Coin(const Vector2D &position, std::shared_ptr<Move::ModeManager> move_manager) : Collectable(position, Vector2D{0.05,0.05}, move_manager) {


    }
} // Logic