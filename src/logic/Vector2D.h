//
// Created by tibov on 25/11/23.
//

#ifndef PROJECTPACMAN_VECTOR2D_H
#define PROJECTPACMAN_VECTOR2D_H
#include <math.h>
namespace Logic {
    /**
     * This Object will give an easy interface to do computation with an x and y value
     * by default will the template parameter be a double because this will be by far the most common use
     * */
    template<typename T = double>
    class Vector2D {
    public:
        /**
         * constructor for Vector2D
         * */
        Vector2D(T x, T y);

        /**
         * empty constructor for Vector2D
         * */
        Vector2D();
        ~Vector2D() = default;

        /**
         * Add 2 Vector2D together
         */
        Vector2D<T> operator+(const Vector2D<T>& other) const;

        /**
         * Add a Vector2D to this Vector2D
         */
        void operator+=(const Vector2D& other);

        /**
         * Subtraction between 2 Vector2D
         */
        Vector2D operator-(const Vector2D<T>& other) const;

        /**
         * Subtract a Vector2D to this Vector2D
         * */
        void operator-=(const Vector2D& other);

        /**
         * get a Vector2D that is a scalar multiplication
         * */
        Vector2D<T> operator*(T multiplier) const;

        /**
         * Do scalar multiplication between values of 2 Vector2D objects
         * */
        Vector2D operator*(const Vector2D& scalar) const;
        /**
         * Do scalar divide between values of 2 Vector2D objects
         * */
        Vector2D operator/(const Vector2D& scalar) const;

        /**
         * Check if 2 vectors are equal
         * */
        bool operator==(const Vector2D& other) const;

        /**
         * get value based on index location
         * index 0: x
         * index 1: y
         * */
        T operator[](int index) const;

        /**
         * Calculate inner product
         * */
        T innerProduct(const Vector2D& other) const;

        /**
         * Calculate length of Vector from 0,0 point
         * */
        T getLength() const;

        /**
         * find angle in radians between these 2 vector2D objects
         * */
        T getAngle(const Vector2D& other) const;

        /**
         * get distance between 2 vectors
         * */
        T getDistance(const Vector2D& other) const;
        /**
         * project this vector on the target vector
         * */
        Vector2D projection(const Vector2D& target) const;

        /**
         * guarantee all values of the vector are positive
         * */
        Vector2D operator+() const;

        /**
         * get normalised version of this Vector2D (length 1)
         * */
        Vector2D get_normalised() const;

        /**
         * get the vector in the other direction of this direction
         * */
        Vector2D getOpposed();

        /**
         * rotate this vector by a given angle in rad
         * */
        Vector2D rotate(double angle);


    private:
        T x;
        T y;
    };




} // Logic

#endif //PROJECTPACMAN_VECTOR2D_H
