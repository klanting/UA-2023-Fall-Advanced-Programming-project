//
// Created by tibov on 25/12/23.
//

#ifndef PROJECTPACMAN_CELLCHANGELOG_H
#define PROJECTPACMAN_CELLCHANGELOG_H
#include "Memento.h"
#include <stack>
#include "Cell.h"
#include "Matrix.h"
namespace Logic {
    namespace WFC {

        class CellChangeLog {
        public:
            CellChangeLog() = default;
            void save(const Matrix<Cell>& m);
            Matrix<Cell> undo();

        private:
            std::stack<Memento<Matrix<Cell>>> history;

        };

    } // WFC
} // Logic

#endif //PROJECTPACMAN_CELLCHANGELOG_H
