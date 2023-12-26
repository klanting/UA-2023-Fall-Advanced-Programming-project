
#include "Coin.h"

namespace Logic {
    Coin::Coin(const Vector2D<> &position, const std::shared_ptr<Move::ModeManager>& move_manager) : Collectable(position, Vector2D{0.035,0.035}, move_manager) {

    }

} // Logic