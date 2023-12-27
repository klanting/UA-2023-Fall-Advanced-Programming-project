//
// Created by tibov on 25/12/23.
//

#ifndef PROJECTPACMAN_CONVERTER_H
#define PROJECTPACMAN_CONVERTER_H
#include "Matrix.h"
#include <vector>
#include "../../Vector2D.h"
#include <memory>
namespace Logic {
    namespace WFC {

        class Converter {
        public:
            Converter(const Matrix<int>& m);
            void exportData() const;
        private:
            bool check(const Vector2D<int>& start_pos, const Vector2D<int>& direction);
            void addWall(const Vector2D<int>& start_pos, const Vector2D<int>& size);
            void addIntersection(const Vector2D<int>& start_pos);
            bool isIntersection(int i, int j);
            Matrix<int> m;
            std::vector<std::pair<Vector2D<>, Vector2D<>>> wall_positions;
            std::vector<std::pair<Vector2D<>, Vector2D<>>> intersection_positions;
            std::unique_ptr<Vector2D<>> ghost_spawn;

            Vector2D<> offset = {0.025, 0.075};
        };

    } // WFC
} // Logic

#endif //PROJECTPACMAN_CONVERTER_H
