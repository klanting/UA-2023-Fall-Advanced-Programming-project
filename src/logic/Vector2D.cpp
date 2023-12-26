//
// Created by tibov on 25/11/23.
//

#include "Vector2D.h"

namespace Logic {

    template class Vector2D<double>;
    template class Vector2D<int>;

    template<typename T>
    Vector2D<T>::Vector2D(T x, T y): x{x}, y{y} {

    }

    template<typename T>
    Vector2D<T> Vector2D<T>::operator+(const Vector2D&other) const {
        return Vector2D{this->x+other.x, this->y+other.y};
    }

    template<typename T>
    Vector2D<T> Vector2D<T>::operator-(const Vector2D&other) const {
        return Vector2D{this->x-other.x, this->y-other.y};
    }

    template<typename T>
    Vector2D<T> Vector2D<T>::operator*(T multiplier) const {
        //scalar multiplication
        return Vector2D{this->x*multiplier, this->y*multiplier};
    }

    template<typename T>
    T Vector2D<T>::innerProduct(const Vector2D &other) const {
        //inner product
        return this->x*other.x + this->y*other.y;
    }

    template<typename T>
    T Vector2D<T>::getLength() const {
        return sqrt(pow(this->x, 2)+pow(this->y, 2));
    }

    template<typename T>
    T Vector2D<T>::getAngle(const Vector2D &other) const {
        double inner_product = innerProduct(other);
        inner_product /= getLength();
        inner_product /= other.getLength();
        return acos(inner_product);
    }

    template<typename T>
    void Vector2D<T>::operator+=(const Vector2D &other) {
        this->x += other.x;
        this->y += other.y;
    }

    template<typename T>
    void Vector2D<T>::operator-=(const Vector2D &other) {
        this->x -= other.x;
        this->y -= other.y;
    }

    template<typename T>
    T Vector2D<T>::getDistance(const Vector2D &other) const {
        return (*this-other).getLength();
    }



    template<typename T>
    Vector2D<T> Vector2D<T>::projection(const Vector2D &target) const{
        double scalar = (*this).innerProduct(target)/ pow(target.getLength(), 2);
        return target*scalar;
    }



    template<typename T>
    Vector2D<T> Vector2D<T>::operator*(const Vector2D &scalar) const {
        return Vector2D(x*scalar.x, y*scalar.y);
    }

    template<typename T>
    T Vector2D<T>::operator[](int index) const {
        if (index == 0){
            return x;
        }

        if (index == 1){
            return y;
        }

        return 0;

    }

    template<typename T>
    Vector2D<T> Vector2D<T>::operator+() const {
        return Vector2D(abs(x), abs(y));
    }

    template<typename T>
    Vector2D<T> Vector2D<T>::get_normalised() const {
        return Vector2D(x/getLength(), y/getLength());
    }

    template<typename T>
    bool Vector2D<T>::operator==(const Vector2D &other) const {
        return abs(this->x - other.x) <= 0.00001 &&  abs(this->y - other.y) <= 0.00001;
    }

    template<typename T>
    Vector2D<T> Vector2D<T>::getOpposed() {
        return Vector2D(-1*x, -1*y);
    }

    template<typename T>
    Vector2D<T> Vector2D<T>::operator/(const Vector2D &scalar) const {
        return Vector2D(x/scalar.x, y/scalar.y);
    }

    template<typename T>
    Vector2D<T> Vector2D<T>::rotate(double angle) {
        return Vector2D(this->x* cos(angle)+this->y*sin(angle), -1*this->x* sin(angle)+this->y*cos(angle));
    }

    template<typename T>
    Vector2D<T>::Vector2D() {
        x = 0;
        y = 0;

    }


} // Logic