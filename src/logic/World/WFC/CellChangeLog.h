//
// Created by tibov on 25/12/23.
//

#ifndef PROJECTPACMAN_CELLCHANGELOG_H
#define PROJECTPACMAN_CELLCHANGELOG_H
#include "Memento.h"
#include <stack>
#include "Cell.h"
namespace Logic {
    namespace WFC {

        class CellChangeLog {
        public:
            CellChangeLog() = default;

        private:
            std::stack<Memento<Cell>> history;

        };

    } // WFC
} // Logic

#endif //PROJECTPACMAN_CELLCHANGELOG_H
