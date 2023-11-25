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
        double innerProduct(const Vector2D& other) const;
        double getLength() const;
        double getAngle(const Vector2D& other) const;
    private:
        double x;
        double y;
    };

} // Logic

#endif //PROJECTPACMAN_VECTOR2D_H
