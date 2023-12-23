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

    void Vector2D::operator+=(const Vector2D &other) {
        this->x += other.x;
        this->y += other.y;
    }

    void Vector2D::operator-=(const Vector2D &other) {
        this->x -= other.x;
        this->y -= other.y;
    }

    double Vector2D::getDistance(const Vector2D &other) const {
        return (*this-other).getLength();
    }

    bool Vector2D::operator<(const Vector2D &other) const {
        return this->x+ this->y < other.x+ other.y;
    }

    Vector2D Vector2D::projection(const Vector2D &target) const{
        double scalar = (*this).innerProduct(target)/ pow(target.getLength(), 2);
        return target*scalar;
    }

    bool Vector2D::operator<=(const Vector2D &other) const {
        return this->x+ this->y <= other.x+ other.y;
    }

    Vector2D Vector2D::operator*(const Vector2D &scalar) const {
        return Vector2D(x*scalar.x, y*scalar.y);
    }

    double Vector2D::operator[](int index) const {
        if (index == 0){
            return x;
        }

        if (index == 1){
            return y;
        }

        return 0;

    }

    Vector2D Vector2D::operator+() const {
        return Vector2D(abs(x), abs(y));
    }

    Vector2D Vector2D::get_normalised() const {
        return Vector2D(x/getLength(), y/getLength());
    }

    bool Vector2D::operator==(const Vector2D &other) const {
        return abs(this->x - other.x) <= 0.00001 &&  abs(this->y - other.y) <= 0.00001;
    }

    Vector2D Vector2D::getOpposed() {
        return Vector2D(-1*x, -1*y);
    }

    Vector2D Vector2D::operator/(const Vector2D &scalar) const {
        return Vector2D(x/scalar.x, y/scalar.y);
    }

    Vector2D Vector2D::rotate(double angle) {
        return Vector2D(this->x* cos(angle)+this->y*sin(angle), -1*this->x* sin(angle)+this->y*cos(angle));
    }



} // Logic