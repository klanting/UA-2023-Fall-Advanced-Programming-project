//
// Created by tibov on 25/11/23.
//

#include "Subject.h"

namespace Logic {
    Subject::Subject(const Vector2D &position, std::unique_ptr<Move::Mode> mode): position{position}, size{Vector2D{0.05, 0.05}},
    move_manager{std::move(mode)} {

    }

    const Vector2D &Subject::getPosition() const {
        return position;
    }

    const Vector2D &Subject::getSize() const {
        return size;
    }
} // Logic