#include "Collectable.h"

namespace Logic {
    Collectable::Collectable(const Vector2D<> &position, const Vector2D<>& size, const std::shared_ptr<Move::ModeManager>& move_manager) : EntityModel(position, size, 0, move_manager) {
        consumable = true;
    }


    bool Collectable::handleDead(const std::vector<std::shared_ptr<EntityModel>>& others) {
        EntityModel::handleDead(others);
        return true;
    }

} // Logic