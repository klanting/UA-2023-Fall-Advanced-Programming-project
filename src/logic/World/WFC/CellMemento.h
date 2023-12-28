//
// Created by tibov on 28/12/23.
//

#ifndef PROJECTPACMAN_CELLMEMENTO_H
#define PROJECTPACMAN_CELLMEMENTO_H
#include "Memento.h"
#include "Cell.h"
#include "Matrix.h"
    namespace Logic::WFC {

        class CellMemento: public Memento<Matrix<Cell>>{
        public:
            CellMemento(const Matrix<Cell>& data);
        private:

        };

    } // WFC
// Logic

#endif //PROJECTPACMAN_CELLMEMENTO_H
