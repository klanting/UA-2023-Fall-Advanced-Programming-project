//
// Created by tibov on 28/12/23.
//

#ifndef PROJECTPACMAN_GRIDGENERATOR_H
#define PROJECTPACMAN_GRIDGENERATOR_H
#include "Cell.h"
#include "Matrix.h"

    namespace Logic::WFC {
        /**
         * Abstract class of grid generators
         * This will ensure to respect the Single Responsibility principle
         * by doing the memento functions in this class
         * */
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
