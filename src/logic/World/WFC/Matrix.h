//
// Created by tibov on 25/12/23.
//

#ifndef PROJECTPACMAN_MATRIX_H
#define PROJECTPACMAN_MATRIX_H
#include <vector>

    namespace Logic::WFC {
        /**
         * This class is used to make a easy to use grid
         * */
        template<typename T>
        class Matrix {
        public:
            /**
             * constructor of the Matrix given a width, height and a default value
             * */
            Matrix(int width, int height, const T& default_value);

            /**
             * get the value present on the entry with width position i and height position j
             * */
            [[nodiscard]] T get(int i, int j) const;

            /**
             * set the value present on the entry with width position i and height position j
             * */
            void set(int i, int j, const T& value);

            [[nodiscard]] int getHeight() const;

            [[nodiscard]] int getWidth() const;

            /**
             * clear the matrix and fill it with the default value
             * */
            void clear(const T& default_value);

            /**
             * check how many times a given value is present on the grid
             * */
            int count(const T& value);
        private:
            std::vector<std::vector<T>> grid;
            int height;
            int width;

        };




    } // WFC
// Logic

#endif //PROJECTPACMAN_MATRIX_H
