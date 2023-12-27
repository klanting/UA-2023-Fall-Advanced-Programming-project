//
// Created by tibov on 25/12/23.
//

#ifndef PROJECTPACMAN_MATRIX_H
#define PROJECTPACMAN_MATRIX_H
#include <vector>
namespace Logic {
    namespace WFC {

        template<typename T>
        class Matrix {
        public:
            Matrix(int width, int height, const T& default_value);
            T get(int i, int j) const;
            void set(int i, int j, const T& value);

            int getHeight() const;

            int getWidth() const;
            void clear(const T& default_value);
            int count(const T& value);
        private:
            std::vector<std::vector<T>> grid;
            int height;
            int width;

        };




    } // WFC
} // Logic

#endif //PROJECTPACMAN_MATRIX_H
