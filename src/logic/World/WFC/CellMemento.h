//
// Created by tibov on 28/12/23.
//

#ifndef PROJECTPACMAN_CELLMEMENTO_H
#define PROJECTPACMAN_CELLMEMENTO_H
#include "Memento.h"
#include "Cell.h"
#include "Matrix.h"
    namespace Logic::WFC {
        /**
         * part of Design Pattern: Memento
         * Derived class of Memento
         * This will make sure a Memento is stored of the a Matrix of cells
         * */

        class CellMemento: public Memento<Matrix<Cell>>{
        public:
            explicit CellMemento(const Matrix<Cell>& data);
        private:

        };

    } // WFC
// Logic

#endif //PROJECTPACMAN_CELLMEMENTO_H
