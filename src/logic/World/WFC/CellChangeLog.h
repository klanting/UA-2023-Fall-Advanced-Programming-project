//
// Created by tibov on 25/12/23.
//

#ifndef PROJECTPACMAN_CELLCHANGELOG_H
#define PROJECTPACMAN_CELLCHANGELOG_H
#include "CellMemento.h"
#include <stack>
#include "Cell.h"
#include "Matrix.h"
#include <functional>

    /**
     * Keeps Log of WFC Grid
     * When needed we are able to rollback this grid
     * */

    namespace Logic::WFC {

        class WFCGridGenerator;

        class CellChangeLog {
        public:
            CellChangeLog(WFCGridGenerator& generator);
            void save();
            void undo();

        private:
            std::stack<CellMemento> history;
            WFCGridGenerator& generator;


        };

    } // WFC
// Logic

#endif //PROJECTPACMAN_CELLCHANGELOG_H
