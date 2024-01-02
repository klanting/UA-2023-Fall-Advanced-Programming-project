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



    namespace Logic::WFC {

        class WFCGridGenerator;

        /**
        * Part of Design Pattern: Memento
        * This class will play the part of the 'CareGiver' in the Memento Design Pattern
        * Keeps Log of WFC Grid
        * When needed we are able to rollback this grid
        * This Object will be used to easily store Memento's of the current Grid State of Cells
        * */
        class CellChangeLog {
        public:
            /**
             * Constructor of CellChangeLog with reference to the generator whose state we want to Save and restore
             * */
            explicit CellChangeLog(WFCGridGenerator& generator);

            /**
             * Save a new state
             * */
            void save();

            /**
             * restore the generator to the last state
             * */
            void undo();

        private:
            /**
             * Stack with all the history states
             * */
            std::stack<CellMemento> history;

            /**
             * generator whose states we are storing
             * */
            WFCGridGenerator& generator;


        };

    } // WFC
// Logic

#endif //PROJECTPACMAN_CELLCHANGELOG_H
