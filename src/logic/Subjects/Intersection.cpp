//
// Created by tibov on 14/12/23.
//

#include "Intersection.h"

namespace Logic {
    Intersection::Intersection(const Vector2D<> &position, const Vector2D<> &size,
                               const std::shared_ptr<Move::ModeManager>& move_manager): EntityModel(position, size, 0, move_manager) {

    }


} // Logic