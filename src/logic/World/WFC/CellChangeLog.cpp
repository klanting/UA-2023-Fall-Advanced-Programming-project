//
// Created by tibov on 25/12/23.
//

#include "CellChangeLog.h"
#include "WFCGridGenerator.h"

    namespace Logic::WFC {
        void CellChangeLog::save() {
            //this will put the grid into the CellMemento class
            history.emplace(generator.save());

        }

        void CellChangeLog::undo() {
            //this will take the last Memento and restore the Generator
            auto m = history.top().getData();
            history.pop();
            generator.restore(m);
        }

        CellChangeLog::CellChangeLog(WFCGridGenerator &generator): generator{generator} {

        }
    } // WFC
// Logic