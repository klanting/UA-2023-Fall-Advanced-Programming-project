//
// Created by tibov on 28/12/23.
//

#ifndef PROJECTPACMAN_GRIDGENERATOR_H
#define PROJECTPACMAN_GRIDGENERATOR_H
#include "Cell.h"
#include "Matrix.h"

    namespace Logic::WFC {

        class GridGenerator {
        public:
            GridGenerator();
            /**
             * Save function to work with the Memento Design Pattern
             * */
            [[nodiscard]] Matrix<Cell> save() const;

            /**
             * Restore function to work with the Memento Design Pattern
             * */
            void restore(const Matrix<Cell>& c);
        protected:
            /**
             * Grid of Cells
             * */
            Matrix<Cell> grid;

        };

    } // WFC
// Logic

#endif //PROJECTPACMAN_GRIDGENERATOR_H
