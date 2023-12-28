//
// Created by tibov on 25/12/23.
//

#ifndef PROJECTPACMAN_CELLCHANGELOG_H
#define PROJECTPACMAN_CELLCHANGELOG_H
#include "CellMemento.h"
#include <stack>
#include "Cell.h"
#include "Matrix.h"

    /**
     * Keeps Log of WFC Grid
     * When needed we are able to rollback this grid
     * */

    namespace Logic::WFC {

        class CellChangeLog {
        public:
            CellChangeLog() = default;
            void save(const Matrix<Cell>& m);
            Matrix<Cell> undo();

        private:
            std::stack<CellMemento> history;

        };

    } // WFC
// Logic

#endif //PROJECTPACMAN_CELLCHANGELOG_H
