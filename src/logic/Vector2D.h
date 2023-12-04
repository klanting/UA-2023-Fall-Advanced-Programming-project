//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_VECTOR2D_H
#define PROJECTPACMAN_VECTOR2D_H
#include <math.h>
namespace Logic {

    class Vector2D {
    public:
        Vector2D(double x, double y);
        Vector2D operator+(const Vector2D& other) const;
        void operator+=(const Vector2D& other);
        Vector2D operator-(const Vector2D& other) const;
        void operator-=(const Vector2D& other);
        Vector2D operator*(double multiplier) const;
        Vector2D operator*(const Vector2D& scalar) const;
        Vector2D operator/(const Vector2D& scalar) const;
        bool operator<(const Vector2D& other) const;
        bool operator<=(const Vector2D& other) const;
        bool operator==(const Vector2D& other) const;
        double operator[](int index) const;

        double innerProduct(const Vector2D& other) const;
        double getLength() const;
        double getAngle(const Vector2D& other) const;
        double getDistance(const Vector2D& other) const;
        Vector2D projection(const Vector2D& target) const;
        Vector2D operator+() const;
        Vector2D get_normalised() const;
        Vector2D getOpposed();


    private:
        double x;
        double y;
    };


} // Logic

#endif //PROJECTPACMAN_VECTOR2D_H
