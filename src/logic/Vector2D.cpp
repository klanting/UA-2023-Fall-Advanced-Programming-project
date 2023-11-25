//
// Created by tibov on 25/11/23.
//

#include "Vector2D.h"

namespace Logic {
    Vector2D::Vector2D(double x, double y): x{x}, y{y} {

    }

    Vector2D Vector2D::operator+(const Vector2D &other) const {
        return Vector2D{this->x+other.x, this->y+other.y};
    }

    Vector2D Vector2D::operator-(const Vector2D &other) const {
        return Vector2D{this->x-other.x, this->y-other.y};
    }

    Vector2D Vector2D::operator*(double multiplier) const {
        //scalar multiplication
        return Vector2D{this->x*multiplier, this->y*multiplier};
    }
} // Logic