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

    double Vector2D::innerProduct(const Vector2D &other) const {
        //inner product
        return this->x*other.x + this->y*other.y;
    }

    double Vector2D::getLength() const {
        return sqrt(pow(this->x, 2)+pow(this->y, 2));
    }

    double Vector2D::getAngle(const Vector2D &other) const {
        double inner_product = innerProduct(other);
        inner_product /= getLength();
        inner_product /= other.getLength();
        return acos(inner_product);
    }


} // Logic