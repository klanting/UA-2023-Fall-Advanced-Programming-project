//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_VECTOR2D_H
#define PROJECTPACMAN_VECTOR2D_H
#include <math.h>
namespace Logic {

    template<typename T = double>
    class Vector2D {
    public:
        Vector2D(T x, T y);
        Vector2D<T> operator+(const Vector2D<T>& other) const;
        void operator+=(const Vector2D& other);
        Vector2D operator-(const Vector2D& other) const;
        void operator-=(const Vector2D& other);
        Vector2D<T> operator*(T multiplier) const;
        Vector2D operator*(const Vector2D& scalar) const;
        Vector2D operator/(const Vector2D& scalar) const;
        bool operator<(const Vector2D& other) const;
        bool operator<=(const Vector2D& other) const;
        bool operator==(const Vector2D& other) const;
        T operator[](int index) const;

        T innerProduct(const Vector2D& other) const;
        T getLength() const;
        T getAngle(const Vector2D& other) const;
        T getDistance(const Vector2D& other) const;
        Vector2D projection(const Vector2D& target) const;
        Vector2D operator+() const;
        Vector2D get_normalised() const;
        Vector2D getOpposed();
        Vector2D rotate(double angle);


    private:
        T x;
        T y;
    };


} // Logic

#endif //PROJECTPACMAN_VECTOR2D_H
