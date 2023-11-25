//
// Created by tibov on 25/11/23.
//

#include "Subject.h"

namespace Logic {
    namespace Model {
    } // Logic
    Subject::Subject(const Vector2D &position, std::unique_ptr<Move::Mode> mode): position{position},
    move_manager{std::move(mode)} {

    }
} // Model