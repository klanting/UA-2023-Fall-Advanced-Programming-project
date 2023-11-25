//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_VECTOR2D_H
#define PROJECTPACMAN_VECTOR2D_H

namespace Logic {

    class Vector2D {
    public:
        Vector2D(double x, double y);
        Vector2D operator+(const Vector2D& other) const;
        Vector2D operator-(const Vector2D& other) const;
        Vector2D operator*(double multiplier) const;
    private:
        double x;
        double y;
    };

} // Logic

#endif //PROJECTPACMAN_VECTOR2D_H
