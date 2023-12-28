//
// Created by tibov on 28/12/23.
//

#include "GridGenerator.h"


    namespace Logic::WFC {
        Matrix<Cell> GridGenerator::save() const {
            return grid;
        }

        void GridGenerator::restore(const Matrix<Cell> &c) {
            grid = c;
        }

        GridGenerator::GridGenerator(): grid{0, 0, Cell{0}}{

        }
    } // WFC
// Logic