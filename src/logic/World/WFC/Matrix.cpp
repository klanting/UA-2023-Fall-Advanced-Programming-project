//
// Created by tibov on 25/12/23.
//

#include "Matrix.h"
#include "Cell.h"
namespace Logic {
    namespace WFC {
        template class Matrix<int>;
        template class Matrix<Cell>;

        template<typename T>
        Matrix<T>::Matrix(int width, int height, const T& default_value): width{width}, height{height} {
            grid.reserve(height);
            for (int j = 0; j<height; j++){
                std::vector<T> row;
                row.reserve(width);
                for (int i = 0; i<width; i++){
                    row.push_back(default_value);
                }
                grid.push_back(row);
            }

        }

        template<typename T>
        T Matrix<T>::get(int i, int j) const {
            return grid[j][i];
        }

        template<typename T>
        void Matrix<T>::set(int i, int j, const T &value) {
            grid[j][i] = value;
        }

        template<typename T>
        int Matrix<T>::getWidth() const {
            return width;
        }

        template<typename T>
        int Matrix<T>::getHeight() const {
            return height;
        }

        template<typename T>
        void Matrix<T>::clear(const T &default_value) {
            for (int j = 0; j<height; j++){
                for (int i = 0; i<width; i++){
                    set(i, j, default_value);
                }
            }
        }

        template<typename T>
        int Matrix<T>::count(const T &value) {
            int count = 0;
            for (int j = 0; j<height; j++){
                for (int i = 0; i<width; i++){
                    if (get(i, j) == value){
                        count++;
                    }
                }
            }

            return count;
        }

    } // WFC
} // Logic